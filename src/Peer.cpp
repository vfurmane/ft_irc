#include "Peer.hpp"

static const char	*CRLF = "\r\n";

Peer::Peer(int fd, struct sockaddr &addr): _fd(fd), _addr(addr), _message(), _nickname(), _user(), _realname(), _mode(), _registered(false)
{
}

Peer::Peer(const Peer &obj): _fd(obj.getFd()), _addr(obj._addr), _message(), _nickname(), _user(), _realname(), _mode(), _registered(false)
{
}

Peer &Peer::operator=(const Peer &rhs)
{
	this->_fd = rhs.getFd();
	return (*this);
}

Peer::~Peer(void)
{
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
	this->_message.clear();
}

bool	Peer::hasCompleteMessage(void) const
{
	return (*(this->_message.end() - 2) == '\r'
			&& *(this->_message.end() - 1) == '\n');
}

const std::string	&Peer::getMessage(void) const
{
	return this->_message;
}

int Peer::getFd(void) const
{
	return this->_fd;
}

bool	Peer::isRegistered(void) const
{
	return this->_registered;
}

void	Peer::registration(const std::string &user, const std::string &mode, const std::string &realname)
{
	this->_registered = true;
	this->_user = user;
	this->_mode = mode;
	this->_realname = realname;
}

const std::string	&Peer::getNickname(void) const
{
	return this->_nickname;
}

void	Peer::setNickname(const std::string &new_nick)
{
	this->_nickname = new_nick;
}

void    Peer::sendMessage(const Message &message) const
{
    send(this->getFd(), (message.input + CRLF).c_str(), (message.input + CRLF).length(), 0);
}

char	*Peer::getStrAddr(void) const
{
	return inet_ntoa(((struct sockaddr_in *)(&this->_addr))->sin_addr);
}

const std::string	&Peer::getUsername(void) const
{
	return this->_user;
}

const std::string 	&Peer::getNickname(void) const
{
	return this->_nickname;
}
