#include "commands.hpp"

int	command_quit(Message &message, Dependencies &deps)
{
	if (message.arguments[0].empty())
		message.arguments[0] = "leaving";
	message.peer.sendMessage(ErrorMessage(message.peer, "Quit: " + message.arguments[0]));
	message.peer.server.sendMessage(QuitMessage(message.peer, message.arguments[0]));
	deps.peers.closeConnection(message.peer.getFd());
	return 0;
}
