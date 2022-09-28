#include "commands.hpp"

int	command_nick(Message &message, Dependencies &deps)
{
	if (message.argCount < 1 || message.arguments[0].empty())
		throw ERR_NONICKNAMEGIVEN();
	message.peer.setNickname(message.arguments[0]);
	for (PeerManager::const_iterator it = deps.peers.begin(); it != deps.peers.end(); ++it)
		it->second.sendMessage(NickMessage(message.peer, message.arguments[0]));
	return 1;
}
