#include "Channel.hpp"

Channel::Channel(const std::string &name): _name(name), _scope(0), _users_in_channel()
{
}

Channel::Channel(const Channel &obj): _name(obj._name), _scope(obj._scope), _users_in_channel(obj._users_in_channel)
{
}

Channel	&Channel::operator=(const Channel &rhs)
{
	this->_name = rhs._name;
	this->_scope = rhs._scope;
	this->_users_in_channel = rhs._users_in_channel;
	return (*this);
}

Channel::~Channel(void)
{
}
