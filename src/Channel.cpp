#include "Channel.hpp"

Channel::Channel(const std::string &name): _name(name), _key(), _flags(0), _users()
{
}

Channel::Channel(const Channel &obj): _name(obj._name), _key(obj._key), _flags(obj._flags), _users(obj._users)
{
}

Channel	&Channel::operator=(const Channel &rhs)
{
	this->_key = rhs._key;
	this->_flags = rhs._flags;
	this->_users = rhs._users;
	return (*this);
}

Channel::~Channel(void)
{
}

void	Channel::setKey(const std::string &key)
{
	this->_key = key;
}

void	Channel::unsetKey(void)
{
	this->_key.clear();
}

bool	Channel::compareKey(const std::string &key) const
{
	return this->_key == key;
}
