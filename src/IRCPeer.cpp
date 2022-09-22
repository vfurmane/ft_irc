#include "IRCPeer.hpp"
#include "TCPPeer.hpp"

IRCPeer::IRCPeer(int fd, struct sockaddr &addr): TCPPeer(fd, addr), _message(), _nickname(), _user(), _realname(), _mode(), _registered(false)
{
}

IRCPeer::IRCPeer(const IRCPeer &obj): TCPPeer(obj), _message(), _nickname()
{
}

IRCPeer &IRCPeer::operator=(const IRCPeer &rhs)
{
	this->_message = rhs._message;
	this->_nickname = rhs._nickname;
	return (*this);
}

IRCPeer::~IRCPeer(void)
{
}

void	IRCPeer::appendMessage(const char *buffer)
{
	this->_message += buffer;
}

void	IRCPeer::clearMessage(void)
{
	this->_message.clear();
}

bool	IRCPeer::hasCompleteMessage(void) const
{
	return (*(this->_message.end() - 2) == '\r'
			&& *(this->_message.end() - 1) == '\n');
}

const std::string	&IRCPeer::getMessage(void) const
{
	return this->_message;
}

bool	IRCPeer::isRegistered(void) const
{
	return (this->_registered);
}

void	IRCPeer::registration(const std::string &user, const std::string &mode, const std::string &realname)
{
	this->_registered = true;
	this->_user = user;
	this->_mode = mode;
	this->_realname = realname;
}

void	IRCPeer::setNickname(const std::string &new_nick)
{
	this->_nickname = new_nick;
}

void	IRCPeer::sendMessage(const IRCMessage &message) const
{
	send(this->getFd(), message.getInput().c_str(), message.getInput().length(), 0);
}
