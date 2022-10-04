#include "User.hpp"

User::User(Peer &peer): _peer(peer)
{
}

User::User(const User &obj): _peer(obj._peer)
{
}

User	&User::operator=(const User &rhs)
{
	this->_peer = rhs._peer;
	return (*this);
}

User::~User(void)
{
}

Peer &User::getPeer(void) const
{
	return this->_peer;
}
