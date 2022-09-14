#include "TCPServer.hpp"
#include <sys/types.h>

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

	if (listen(_sockfd, BACKLOG))
		throw sysCallError("listen", strerror(errno));
}
