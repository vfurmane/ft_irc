#include "commands.hpp"

int		command_ping(Message &message, Dependencies &deps)
{
	(void)deps;
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), "PING");
	message.peer.sendMessage(PongMessage(message.peer, message.arguments[0]));
	return 1;
}
