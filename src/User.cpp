#include "User.hpp"

User::User(Peer &peer): peer(peer)
{
}

User::User(const User &obj): peer(obj.peer)
{
}

User	&User::operator=(const User &rhs)
{
	this->peer = rhs.peer;
	return (*this);
}

User::~User(void)
{
}
