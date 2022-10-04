#include "Channel.hpp"

Channel::Channel(const std::string &name): _name(name), _flags(0), _users()
{
}

Channel::Channel(const Channel &obj): _name(obj._name), _flags(obj._flags), _users(obj._users)
{
}

Channel	&Channel::operator=(const Channel &rhs)
{
	this->_flags = rhs._flags;
	this->_users = rhs._users;
	return (*this);
}

Channel::~Channel(void)
{
}
