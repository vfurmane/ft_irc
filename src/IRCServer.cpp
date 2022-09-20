#include "IRCServer.hpp"

IRCServer::IRCServer(char *port): TCPServer(port)
{
	TCPServer::setHandler(HDL_MESSAGE, handleIRCMessage);
}

IRCServer::~IRCServer(void)
{

}

void IRCServer::setHandler(e_handler_type type, int (*handler)(TCPPeer *, epoll_event *))
{
	(void)type;
	(void)handler;
	throw cannotSetHandler();
}
