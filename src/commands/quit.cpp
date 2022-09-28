#include "commands.hpp"

int	command_quit(Message &message, Dependencies &deps)
{
	message.peer.sendMessage(ErrorMessage(message.peer, message.arguments[0]));
	deps.peers.closeConnection(message.peer.getFd());
	return 0;
}
