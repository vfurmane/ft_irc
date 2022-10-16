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

bool	_base_channel::isValidName(const std::string &channel)
{
	if (channel.empty() || channel.size() > 50)
		return false;

	std::string::const_iterator	it = channel.begin();

	if (*it != '#')
		return false;
	for (++it; it != channel.end(); ++it)
	{
		if (*it == ' ' || *it == '\a' || *it == ',' || *it == ':')
			return false;
	}
	return true;
}

_base_channel	_base_channel::parse(const std::string &channel)
{
	if (channel.empty() || channel.size() > 50)
		throw InvalidChannelName();

	std::string::const_iterator	it = channel.begin();

	if (*it != '#')
		throw InvalidChannelName();
	for (++it; it != channel.end(); ++it)
	{
		if (*it == ' ' || *it == '\a' || *it == ',' || *it == ':')
			throw InvalidChannelName();
	}
	return channel.substr(1);
}

std::string	_base_channel::stringify(void) const
{
	return static_cast<char>(this->_namespace) + this->_name;
}

Channel::Channel(ChannelManager &manager, const std::string &name): _base_channel(name), users(), manager(manager), _key(), _flags(0), _creator(NULL)
{
}

Channel::Channel(ChannelManager &manager, const _base_channel &obj): _base_channel(obj), users(), manager(manager), _key(), _flags(0), _creator(NULL)
{
}

Channel::Channel(const Channel &obj): _base_channel(obj), users(obj.users), manager(obj.manager), _key(obj._key), _flags(obj._flags) , _creator(NULL)
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

void	Channel::setCreator(User &user)
{
	this->_creator = &user;
}

User	&Channel::add(Peer &peer)
{
	return this->users.add(User(peer, *this));
}

void	Channel::remove(const User &user)
{
	if (&this->_creator->peer == &user.peer)
		this->_creator = NULL;
	this->users.remove(user);
	if (this->manager.empty())
		manager.remove(this->getName());
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
