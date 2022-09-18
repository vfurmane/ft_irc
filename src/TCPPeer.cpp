#include "TCPPeer.hpp"

TCPPeer::TCPPeer(int fd, struct sockaddr &addr): _fd(fd), _addr(addr)
{
}

TCPPeer::TCPPeer(const TCPPeer &obj): _fd(obj.getFd()), _addr(obj._addr)
{
}

TCPPeer &TCPPeer::operator=(const TCPPeer &rhs)
{
	this->_fd = rhs.getFd();
	return (*this);
}

TCPPeer::~TCPPeer(void)
{
}

int	TCPPeer::close(void) const
{
	return ::close(this->_fd);
}

int TCPPeer::getFd(void) const
{
	return this->_fd;
}

char	*TCPPeer::getStrAddr(void) const
{
	return inet_ntoa(((struct sockaddr_in *)(&this->_addr))->sin_addr);
}
