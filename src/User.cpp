#include "User.hpp"

User::User(Peer &peer, Channel &channel): peer(peer), channel(channel), _status(CHANNEL_USER) 
{
}

User::User(const User &obj): peer(obj.peer), channel(obj.channel), _status(obj._status)
{
}

User	&User::operator=(const User &rhs)
{
	this->peer = rhs.peer;
	this->_status = rhs._status;
	return (*this);
}

User::~User(void)
{
}

uint8_t	User::getStatus(void) const
{
	return this->_status;
}

void	User::setStatus(t_user_status status)
{
	this->_status = status;
}
