#include "commands.hpp"

void	command_quit(IRCMessage &message, Dependencies &deps)
{
	IRCPeerManager.closeConnection(message.peer.getFd());
}
