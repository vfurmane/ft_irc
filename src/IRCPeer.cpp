#include "IRCPeer.hpp"
#include "TCPPeer.hpp"

IRCPeer::IRCPeer(int fd, struct sockaddr &addr): TCPPeer(fd, addr), _message()
{
}

IRCPeer::IRCPeer(const IRCPeer &obj): TCPPeer(obj), _message()
{
}

IRCPeer &IRCPeer::operator=(const IRCPeer &rhs)
{
	this->_message = rhs._message;
	return (*this);
}

IRCPeer::~IRCPeer(void)
{
}

void	IRCPeer::appendMessage(const char *buffer)
{
	this->_message += buffer;
}
