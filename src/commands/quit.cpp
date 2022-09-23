#include "commands.hpp"

void	command_quit(IRCMessage &message, Dependencies &deps)
{
	deps.peers.closeConnection(message.peer.getFd());
	message.peer.sendMessage(ErrorMessage(message.peer, message.getArguments()[]));
}
