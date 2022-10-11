#include "Channel.hpp"

_base_channel::_base_channel(const std::string &name): _name(toIRCLower(name)), _namespace(PUBLIC)
{
}

_base_channel::_base_channel(const _base_channel &obj): _name(obj._name), _namespace(PUBLIC)
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

const t_channel_namespace	&_base_channel::getNamespace(void) const
{
	return this->_namespace;
}

std::string	_base_channel::stringify(void) const
{
	return static_cast<char>(this->_namespace) + this->_name;
}

Channel::Channel(const std::string &name): _base_channel(name), users(), _key(), _flags(0) 
{
}

Channel::Channel(const _base_channel &obj): _base_channel(obj), users(), _key(), _flags(0)
{
}

Channel::Channel(const Channel &obj): _base_channel(obj), users(obj.users), _key(obj._key), _flags(obj._flags) 
{
}

Channel	&Channel::operator=(const Channel &rhs)
{
	this->_key = rhs._key;
	this->_flags = rhs._flags;
	this->users = rhs.users;
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
	if (this->_key.empty())
		return true;
	return this->_key == key;
}

User	&Channel::add(Peer &peer)
{
	return this->users.add(User(peer, *this));
}

void	Channel::remove(const User &user)
{
	this->users.remove(user);
}

void    Channel::sendMessage(const Message &message) const
{
#ifndef NDEBUG
	std::cerr << message.peer.generatePrefix() << "= " << this->stringify() << " => " << message.input << std::endl;
#endif
	Message	prefixed_message = message;
	prefixed_message.updatePrefixFromPeer();
	prefixed_message.updateInputFromFields();
	for (UserManager::const_iterator it = users.begin(); it != users.end(); ++it)
	{
		send(it->second.peer.getFd(), (prefixed_message.input + CRLF).c_str(), (prefixed_message.input + CRLF).length(), 0);
	}
}
