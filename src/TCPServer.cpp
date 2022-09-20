#include "TCPServer.hpp"

static const char	*g_handler_type_str[] = {"HDL_MESSAGE"};

TCPServer::TCPServer(char *port) : _sockfd(-1), _epollfd(-1), _peers(*this), _handlers()
{
#ifndef NDEBUG
	std::cerr << "Creating a TCP server..." << std::endl;
#endif
	this->_bindNewSocketToPort(port);
	std::memset(&this->_handlers, 0, sizeof(this->_handlers));
#ifndef NDEBUG
	std::cerr << "Done creating the TCP server!" << std::endl;
#endif
}

TCPServer::~TCPServer(void)
{
	if (close(this->_sockfd) == -1)
		throw sysCallError("close", strerror(errno));
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
			if (close(this->_sockfd) == -1)
				throw sysCallError("close", strerror(errno));
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

void	TCPServer::_addFdToEpoll(int new_fd) const
{
	struct epoll_event event;

	event.events = EPOLLIN;
	event.data.fd = new_fd;
	if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, new_fd, &event) == -1)
	{
		close(this->_epollfd);
		close(this->_sockfd);
		throw sysCallError("epoll_ctl", strerror(errno));
	}
#ifndef NDEBUG
	std::cerr << "Added fd " << new_fd << " to epoll!" << std::endl;
#endif
}

void	TCPServer::_handleReadyFds(int event_count, struct epoll_event *events)
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
			this->_addFdToEpoll(this->_peers.acceptConnection());
		}
		else
		{
#ifndef NDEBUG
			std::cerr << "New message..." << std::endl;
#endif
			if (this->_handlers[HDL_MESSAGE](&this->_peers.get(events[i].data.fd), &events[i]) == -1)
			{
				this->_peers.closeConnection(events[i].data.fd);
			}
		}
	}
}

void	TCPServer::listen(void)
{
	struct epoll_event	events[MAX_EVENTS];

	for(size_t i = 0; i < this->_handlers_nb; i++)
	{
		if (this->_handlers[i] == 0)
			throw handlersNotSet();
	}
	if (::listen(_sockfd, BACKLOG))
		throw sysCallError("listen", strerror(errno));
#ifndef NDEBUG
	std::cerr << "Set the socket to listening!" << std::endl;
#endif

	this->_epollfd = epoll_create1(0);
	if (this->_epollfd == -1)
	{
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
		throw sysCallError("close", strerror(errno));
	}
}

void	TCPServer::setHandler(e_handler_type type, int (*handler)(TCPPeer *, epoll_event *))
{
	this->_handlers[type] = handler;
#ifndef NDEBUG
	std::cerr << "Set handler for " << g_handler_type_str[type] << "!" << std::endl;
#endif
}

int	TCPServer::getEpollFd(void) const
{
	return this->_epollfd;
}

int	TCPServer::getSocketFd(void) const
{
	return this->_sockfd;
}
