#include "commands.hpp"

void	command_quit(Message &message, Dependencies &deps)
{
	deps.peers.closeConnection(message.peer.getFd());
	message.peer.sendMessage(ErrorMessage(message.peer, message.arguments[0]));
}
