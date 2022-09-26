#include "commands.hpp"

void	command_nick(IRCMessage &message, Dependencies &deps)
{
	if (message.getArgsCount() < 1 || message.getArguments()[0].empty())
		throw ERR_NONICKNAMEGIVEN();
	message.peer.setNickname(message.getArguments()[0]);
	for (IRCPeerManager::const_iterator it = deps.peers.begin(); it != deps.peers.end(); ++it)
		it->second.sendMessage(NickMessage(message.peer, message.getArguments()[0]));
}
