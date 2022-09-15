#include "Peer.hpp"

Peer::Peer(int fd, uint16_t address): _fd(fd), _address(address)
{
}

Peer::Peer(const Peer &obj): _fd(obj.getFd()), _address(obj.getAddress())
{
}

Peer &Peer::operator=(const Peer &rhs)
{
	this->_fd = rhs.getFd();
	this->_address = rhs.getAddress();
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

uint16_t Peer::getAddress(void) const
{
	return this->_address;
}
