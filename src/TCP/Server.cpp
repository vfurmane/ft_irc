#include "TCP/Server.hpp"
#include <stdio.h> // TODO Remove le header

static const char	*g_handler_type_str[] = {"HDL_MESSAGE"};

namespace TCP {

	Server::Server(char *port) : _sockfd(-1), _epollfd(-1), _peers(*this), _handlers()
	{
#ifndef NDEBUG
		std::cerr << "Creating a TCP server..." << std::endl;
#endif
		this->_bindNewSocketToPort(port);
#ifndef NDEBUG
		std::cerr << "Done creating the TCP server!" << std::endl;
#endif
	}
	
	Server::Server(const Server &obj) : _sockfd(-1), _epollfd(-1), _peers(*this), _handlers()
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
	
#ifndef NDEBUG
		std::cerr << "Trying addresses for bind..." << std::endl;
#endif
		struct addrinfo *p;
		for (p = servinfo; p != NULL; p = p->ai_next)
		{
			if ((this->_sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
			{
#ifndef NDEBUG
				std::cerr << "socket: " << strerror(errno) << std::endl;
#endif
				continue;
			}
#ifndef NDEBUG
			std::cerr << "Created a socket -> " << this->_sockfd << "!" << std::endl;
#endif
	
			const int yes = 1;
			if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1)
			{
				throw sysCallError("setsockopt", strerror(errno));
			}
#ifndef NDEBUG
			std::cerr << "Set socket option SO_REUSEADDR!" << std::endl;
#endif
	
			if (bind(this->_sockfd, p->ai_addr, p->ai_addrlen))
			{
				close(this->_sockfd);
#ifndef NDEBUG
				std::cerr << "bind: " << strerror(errno) << std::endl;
#endif
				continue;
			}
#ifndef NDEBUG
			std::cerr << "Bound socket to port " << port << "!" << std::endl;
#endif
	
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
#ifndef NDEBUG
		std::cerr << "Added fd " << new_fd << " to epoll!" << std::endl;
#endif
	}

	void	Server::_handleReadyFds(int event_count, struct epoll_event *events)
	{
		for (int i = 0; i < event_count; i++)
		{
#ifndef NDEBUG
			std::cerr << "-> fd no " << events[i].data.fd << std::endl;
#endif
			if (events[i].data.fd == this->_sockfd)
			{
#ifndef NDEBUG
				std::cerr << "New connection..." << std::endl;
#endif
				this->_addFdToEpoll(this->_peers.acceptNewConnection());
			}
			else
			{
#ifndef NDEBUG
				std::cerr << "New message..." << std::endl;
#endif
				if (this->_handlers[HDL_MESSAGE](&events[i]) == -1)
				{
					this->_peers.remove(events[i].data.fd);
				}
			}
		}
	}
	
	void	Server::listen(void)
	{
		struct epoll_event	events[MAX_EVENTS];
	
		if (::listen(_sockfd, BACKLOG))
			throw sysCallError("listen", strerror(errno));
#ifndef NDEBUG
		std::cerr << "Set the socket to listening!" << std::endl;
#endif
	
		this->_epollfd = epoll_create1(0);
		if (this->_epollfd == -1)
		{
			// Debug Log eventually
			throw sysCallError("epoll_create1", strerror(errno));
		}
		this->_addFdToEpoll(this->_sockfd);
	
#ifndef NDEBUG
		std::cerr << "Starting the listening loop..." << std::endl;
#endif
		while (true) {
			int event_count = epoll_wait(this->_epollfd, events, MAX_EVENTS, TIMEOUT);
#ifndef NDEBUG
			if (event_count > 0)
				std::cerr << event_count << " fds ready..." << std::endl;
#endif
			this->_handleReadyFds(event_count, events);
		}
#ifndef NDEBUG
		std::cerr << "Got out of the listening loop!" << std::endl;
#endif
	
		if (close(this->_epollfd) == -1)
		{
			// Debug Log eventually
			throw sysCallError("close", strerror(errno));
		}
	}

	void	Server::setHandler(e_handler_type type, int (*handler)(epoll_event *))
	{
		this->_handlers[type] = handler;
#ifndef NDEBUG
		std::cerr << "Set handler for " << g_handler_type_str[type] << "!" << std::endl;
#endif
	}

}

int	TCP::Server::getEpollFd(void) const
{
	return this->_epollfd;
}

int	TCP::Server::getSocketFd(void) const
{
	return this->_sockfd;
}
