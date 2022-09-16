#include "TCP/Server.hpp"
#include <stdio.h> // TODO Remove le header

namespace TCP {

	Server::Server(char *port) : _sockfd(-1), _epollfd(-1), _peer_managers(), _handlers()
	{
		this->_bindNewSocketToPort(port);
	}
	
	Server::Server(const Server &obj) : _sockfd(-1), _epollfd(-1), _peer_managers(), _handlers()
	{
		*this = obj;
	}
	
	Server::~Server(void)
	{
		close(this->_sockfd);
	}
	
	Server	&Server::operator=(const Server &rhs)
	{
		(void)rhs;
		return *this;
	}
	
	void		Server::_bindNewSocketToPort(char *port)
	{
		int				status;
		struct addrinfo	hints, *servinfo;
	
		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;
	
		if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0)
			throw sysCallError("getaddrinfo", gai_strerror(status));
	
		struct addrinfo *p;
		for (p = servinfo; p != NULL; p = p->ai_next)
		{
			if ((this->_sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
			{
				// DEBUG LOG eventually
				continue;
			}
	
			const int yes = 1;
			if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
			{
				throw sysCallError("setsockopt", strerror(errno));
			}
	
			if (bind(this->_sockfd, p->ai_addr, p->ai_addrlen))
			{
				close(this->_sockfd);
				// DEBUG LOG eventually
				continue;
			}
	
			break;
		}
		freeaddrinfo(servinfo);
	
		if (p == NULL)
			throw noBindableAddress();
	}
	
	void	Server::_addFdToEpoll(int new_fd) const
	{
		struct epoll_event event;
	
		event.events = EPOLLIN;
		event.data.fd = new_fd;
		if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, new_fd, &event) == -1)
		{
			// TODO close all the fds given to epoll inside another function
			close(this->_epollfd);
			close(this->_sockfd);
			throw Server::sysCallError("epoll_ctl", strerror(errno));
		}
	}
	
	void	Server::_registerNewPeer(int new_fd, struct sockaddr &addr)
	{
		this->_addFdToEpoll(new_fd);
		this->_peer_managers.addPeer(Peer(new_fd, addr));
	}
	
	void	Server::_handleReadyFds(int event_count, struct epoll_event *events)
	{
		for (int i = 0; i < event_count; i++)
		{
			if (events[i].data.fd == this->_sockfd)
			{
				struct sockaddr their_addr;
				socklen_t sin_size = sizeof their_addr;
	
				int new_fd;
				if ((new_fd = accept(this->_sockfd, &their_addr, &sin_size)) == -1)
				{
					// TODO close all the fds given to epoll inside another function
					close(this->_epollfd);
					close(this->_sockfd);
					throw Server::sysCallError("accept", strerror(errno));
				}
	
				printf("New connection from %s\n", inet_ntoa(((struct sockaddr_in *)(&their_addr))->sin_addr)); // DEBUG
	
				this->_registerNewPeer(new_fd, their_addr);
			}
			else
			{
				if (this->_handlers[HDL_MESSAGE](&events[i]) == -1)
				{
					printf("Closing connection from %s\n", this->_peer_managers[events[i].data.fd].getStrAddr()); // DEBUG
					close(events[i].data.fd);
					this->_peer_managers.removePeer(events[i].data.fd);
				}
			}
		}
	}
	
	void	Server::listen(void)
	{
		struct epoll_event	events[MAX_EVENTS];
	
		if (::listen(_sockfd, BACKLOG))
			throw sysCallError("listen", strerror(errno));
	
		this->_epollfd = epoll_create1(0);
		if (this->_epollfd == -1)
		{
			// Debug Log eventually
			throw sysCallError("epoll_create1", strerror(errno));
		}
		this->_addFdToEpoll(this->_sockfd);
	
		while (true) {
			int event_count = epoll_wait(this->_epollfd, events, MAX_EVENTS, TIMEOUT);
			this->_handleReadyFds(event_count, events);
		}
	
		if (close(this->_epollfd) == -1)
		{
			// Debug Log eventually
			throw sysCallError("close", strerror(errno));
		}
	}

	void	Server::setHandler(e_handler_type type, int (*handler)(epoll_event *))
	{
		this->_handlers[type] = handler;
	}

}
