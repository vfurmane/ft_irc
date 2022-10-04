#include "commands.hpp"

int	command_quit(Message &message, Dependencies &deps)
{
	std::string	msg;

	msg = "Quit: " + message.arguments[0];
	message.peer.sendMessage(ErrorMessage(message.peer, msg));
	deps.peers.closeConnection(message.peer.getFd());
	return 0;
}
