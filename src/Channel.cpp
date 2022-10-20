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

Channel::Channel(ChannelManager &manager, const std::string &name): _base_channel(name), users(), manager(manager), _key(), _flags(0), _creator(NULL), _invitations()
{
}

Channel::Channel(ChannelManager &manager, const _base_channel &obj): _base_channel(obj), users(), manager(manager), _key(), _flags(0), _creator(NULL), _invitations()
{
}

Channel::Channel(const Channel &obj): _base_channel(obj), users(obj.users), manager(obj.manager), _key(obj._key), _flags(obj._flags) , _creator(NULL), _invitations()
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

bool	Channel::hasFlag(t_channel_flag flag) const
{
	return (this->getFlags() & flag) != 0;
}

uint32_t	Channel::getFlags(void) const
{
	return this->_flags;
}

void	Channel::setFlag(t_channel_flag flag)
{
	this->_flags |= flag;
}

void	Channel::unsetFlag(t_channel_flag flag)
{
	this->_flags &= ~flag;
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
	user.setStatus(CHANNEL_CREATOR);
}

void	Channel::addInvitation(const Peer &peer)
{
	this->_invitations.push_back(peer.getFd());
}

bool	Channel::isInvited(const Peer &peer) const
{
	return std::find(this->_invitations.begin(), this->_invitations.end(), peer.getFd()) != this->_invitations.end();
}

void	Channel::removeInvitation(const Peer &peer)
{
	std::vector<int>::iterator it;
	it = std::find(this->_invitations.begin(), this->_invitations.end(), peer.getFd());
	if (it != this->_invitations.end())
		this->_invitations.erase(it);
}

User	&Channel::add(Peer &peer)
{
#ifndef NDEBUG
	std::cerr << peer.generatePrefix() << " joins " << this->stringify() << std::endl;
#endif
	return this->users.add(User(peer, *this));
}

void	Channel::remove(const Peer &peer)
{
	if (this->_creator != NULL && &this->_creator->peer == &peer)
		this->_creator = NULL;
	this->users.remove(peer);
	if (this->manager.empty())
		manager.remove(this->getName());
	if (this->isInvited(peer))
		this->removeInvitation(peer);
#ifndef NDEBUG
	std::cerr << peer.generatePrefix() << " has left " << this->stringify() << std::endl;
#endif
}

void	Channel::remove(const User &user)
{
	this->remove(user.peer);
}

void	Channel::sendMessage(const Message &message) const
{
#ifndef NDEBUG
	std::cerr << "Sending message to channel " << this->stringify() << std::endl;
#endif
	Message	prefixed_message = message;
	prefixed_message.updatePrefixFromPeer();
	prefixed_message.updateInputFromFields();
	for (UserManager::const_iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it->second.peer.getFd() == message.peer.getFd())
			continue ;
		it->second.peer.sendMessage(prefixed_message);
	}
}
