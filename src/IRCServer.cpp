#include "IRCServer.hpp"

int	handleIRCMessage(epoll_event *event); // REMOVE

IRCServer::IRCServer(char *port): TCPServer(port)
{
	TCPServer::setHandler(HDL_MESSAGE, handleIRCMessage);
}

IRCServer::~IRCServer(void)
{

}

void IRCServer::setHandler(e_handler_type type, int (*handler)(epoll_event *))
{
	(void)type;
	(void)handler;
	throw cannotSetHandler();
}
