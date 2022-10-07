#include "Channel.hpp"

_base_channel::_base_channel(const std::string &name): _name(name)
{
}

_base_channel::_base_channel(const _base_channel &obj): _name(obj._name)
{
}

_base_channel	&_base_channel::operator=(const _base_channel &rhs)
{
	(void)rhs;
	return (*this);
}

_base_channel::~_base_channel(void)
{
}

const std::string	&_base_channel::getName(void) const
{
	return this->_name;
}

Channel::Channel(const std::string &name): _base_channel(name), _key(), _flags(0), _users()
{
}

Channel::Channel(const _base_channel &obj): _base_channel(obj), _key(), _flags(0), _users()
{
}

Channel::Channel(const Channel &obj): _base_channel(obj), _key(obj._key), _flags(obj._flags), _users(obj._users)
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

User	&Channel::add(const User &user)
{
	return this->_users.add(user).first->second;
}

void	Channel::remove(const User &user)
{
	this->_users.remove(user);
}
