#include "User.hpp"

User::User(Peer &peer, Channel &channel): peer(peer), channel(channel)
{
}

User::User(const User &obj): peer(obj.peer), channel(obj.channel)
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
