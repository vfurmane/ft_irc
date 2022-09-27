#include "Peer.hpp"

Peer::Peer(int fd, struct sockaddr &addr): _fd(fd), _addr(addr)
{
}

Peer::Peer(const Peer &obj): _fd(obj.getFd()), _addr(obj._addr)
{
}

Peer &Peer::operator=(const Peer &rhs)
{
	this->_fd = rhs.getFd();
	return (*this);
}

Peer::~Peer(void)
{
}

int	Peer::close(void) const
{
	return ::close(this->_fd);
}

void	Peer::appendMessage(const char *buffer)
{
	this->_message += buffer;
}

void	Peer::clearMessage(void)
{
	this->_message.clear();
}

bool	Peer::hasCompleteMessage(void) const
{
	return (*(this->_message.end() - 2) == '\r'
			&& *(this->_message.end() - 1) == '\n');
}

const std::string	&Peer::getMessage(void) const
{
	return this->_message;
}

int Peer::getFd(void) const
{
	return this->_fd;
}

char	*Peer::getStrAddr(void) const
{
	return inet_ntoa(((struct sockaddr_in *)(&this->_addr))->sin_addr);
}
