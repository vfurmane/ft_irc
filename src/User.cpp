#include "User.hpp"

User::User(Peer &peer, Channel &channel): peer(peer), channel(channel), flags(channel_user) 
{
}

User::User(const User &obj): peer(obj.peer), channel(obj.channel), flags(obj.flags)
{
}

User	&User::operator=(const User &rhs)
{
	this->peer = rhs.peer;
	this->flags = rhs.flags;
	return (*this);
}

User::~User(void)
{
}
