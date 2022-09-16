#include "TCP/Peer.hpp"

Peer::Peer(int fd): _fd(fd)
{
}

Peer::Peer(const Peer &obj): _fd(obj.getFd())
{
}

Peer &Peer::operator=(const Peer &rhs)
{
	this->_fd = rhs.getFd();
	return (*this);
}

Peer::~Peer(void)
{
	close(this->_fd);
}

int Peer::getFd(void) const
{
	return this->_fd;
}
