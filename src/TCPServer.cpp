#include "TCPServer.hpp"
#include <stdio.h> // TODO Remove le header

TCPServer::TCPServer(char *port)
{
	this->_bindNewSocketToPort(port);
}

TCPServer::TCPServer(const TCPServer &obj)
{
	*this = obj;
}

TCPServer::~TCPServer(void)
{
	close(this->_sockfd);
}

TCPServer	&TCPServer::operator=(const TCPServer &rhs)
{
	(void)rhs;
	return *this;
}

void		TCPServer::_bindNewSocketToPort(char *port)
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

	if (::listen(_sockfd, BACKLOG))
		throw sysCallError("listen", strerror(errno));
}

void	TCPServer::_addFdToEpoll(int new_fd) const
{
	struct epoll_event event;

	event.events = EPOLLIN;
	event.data.fd = new_fd;
	if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, new_fd, &event) == -1)
	{
		// TODO close all the fds given to epoll inside another function
		close(this->_epollfd);
		close(this->_sockfd);
		throw TCPServer::sysCallError("epoll_ctl", strerror(errno));
	}
}

void	TCPServer::_handleReadyFds(int event_count, struct epoll_event *events) const
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
				throw TCPServer::sysCallError("accept", strerror(errno));
			}

			printf("New connection from %s\n", inet_ntoa(((struct sockaddr_in *)(&their_addr))->sin_addr)); // DEBUG

			this->_addFdToEpoll(new_fd);
		}
		else
		{
			char	buffer[MAX_READ + 1];
			int bytes_read = recv(events[i].data.fd, buffer, MAX_READ, 0);

			if (bytes_read == 0)
			{
				struct sockaddr their_addr;
				socklen_t sin_size = sizeof their_addr;
				getpeername(events[i].data.fd, &their_addr, &sin_size);
				printf("Closed connection from %s\n", inet_ntoa(((struct sockaddr_in *)(&their_addr))->sin_addr)); // DEBUG
				close(events[i].data.fd);
			}
			else
			{
				buffer[bytes_read] = '\0';
				printf("%s", buffer); // DEBUG
			}
		}
	}
}

void	TCPServer::listen(void)
{
	struct epoll_event	events[MAX_EVENTS];
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
