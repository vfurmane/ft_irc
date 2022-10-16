#include "Peer.hpp"

Peer::Peer(Server &server, int fd, const struct sockaddr &addr): server(server), _fd(fd), _addr(addr), _message(), _nickname(), _username(), _realname(), _password(), _registered(false)
{
}

Peer::Peer(const Peer &obj): server(obj.server), _fd(obj.getFd()), _addr(obj._addr), _message(), _nickname(), _username(), _realname(), _password(), _registered(false)
{
}

Peer &Peer::operator=(const Peer &rhs)
{
	(void)rhs;
	return (*this);
}

Peer::~Peer(void)
{
}

Channel	&Peer::createChannel(const _base_channel &base_channel)
{
	Channel &channel = this->server.channels.add(base_channel);
	User	&user = channel.add(*this);
	channel.setCreator(user);
	return channel;
}

int	Peer::close(void) const
{
	return ::close(this->_fd);
}

void	Peer::appendMessage(const char *buffer)
{
	this->_message += buffer;
}

void	Peer::clearMessage(void)
{
	std::string::size_type crlf_pos = this->_message.find(CRLF);

	if (crlf_pos == std::string::npos)
		this->_message.clear();
	else
		this->_message = this->_message.substr(crlf_pos + 2);
}

bool	Peer::hasCompleteMessage(void) const
{
	std::string::size_type crlf_pos = this->_message.find(CRLF);

	return crlf_pos != std::string::npos;
}

const std::string	&Peer::getMessage(void) const
{
	return this->_message;
}

int Peer::getFd(void) const
{
	return this->_fd;
}

void	Peer::setUsername(const std::string &username)
{
	if (this->_username.empty())
		this->_username = username;
}

void	Peer::setRealName(const std::string &realname)
{
	if (this->_realname.empty())
		this->_realname = realname;
}

bool	Peer::hasAllFields(void) const
{
	return !(this->_nickname.empty() || this->_username.empty() || this->_realname.empty());
}

bool	Peer::isRegistered(void) const
{
	return this->_registered;
}

int	Peer::registration(const std::string &password)
{
	if (!password.empty() && this->getPassword() != password)
	{
		this->sendMessage(ErrorMessage(*this, "Access denied by configuration"));
		this->server.peers.closeConnection(this->getFd());
		return 0;
	}
	this->_registered = true;
	this->sendMessage(RPL_WELCOME(*this));
	this->sendMessage(RPL_YOURHOST(*this));
	this->sendMessage(RPL_CREATED(*this));
	this->sendMessage(RPL_MYINFO(*this));
	return 1;
}

void	Peer::setNickname(const std::string &new_nick)
{
	this->_nickname = new_nick;
}

void	Peer::setPassword(const std::string &new_password)
{
	this->_password = new_password;
}

std::string	Peer::generatePrefix(void) const
{
	std::string	ret;

	if (!this->_nickname.empty())
		ret += this->_nickname; 
	if (!this->_username.empty())
		ret += "!" + this->_username; 
	if (!this->_nickname.empty() || !this->_username.empty())
		ret += "@";
	ret += this->getStrAddr(); 
	return ret;
}

void    Peer::sendMessage(const Message &message) const
{
#ifndef NDEBUG
	std::cerr << this->generatePrefix() << "> " << message.input << std::endl;
#endif
    send(this->getFd(), (message.input + CRLF).c_str(), (message.input + CRLF).length(), 0);
}

void    Peer::sendMessage(const AIRCError &error) const
{
	const std::string	message = error.what();
#ifndef NDEBUG
	std::cerr << this->generatePrefix() << "> " << message << std::endl;
#endif
    send(this->getFd(), (message + CRLF).c_str(), (message + CRLF).length(), 0);
}

void	Peer::leaveAllChannels(void)
{
	for (ChannelManager::iterator it = this->server.channels.begin(); it != this->server.channels.end(); ++it)
	{
		if (it->second.users.has(this->getUsername()))
			it->second.users.remove(this->getUsername());
	}
}

char	*Peer::getStrAddr(void) const
{
	return inet_ntoa(((struct sockaddr_in *)(&this->_addr))->sin_addr);
}

const std::string	&Peer::getUsername(void) const
{
	return this->_username;
}

const std::string 	&Peer::getNickname(void) const
{
	return this->_nickname;
}

const std::string	&Peer::getPassword(void) const
{
	return this->_password;
}
