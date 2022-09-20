#include "TCPServer.hpp"

void	command_nick(IRCMessage &message, Dependencies &deps)
{
	if (message.args_count < 1)
		throw ERR_NONICKNAMEGIVEN();
	deps.peers.get(message.fd).setNickname(message.args[0]);
	for (PeerManager::const_iterator it = deps.peers.begin(); it != deps.peers.end(); ++it)
	{
		if (*it.getFd() == message.peer.getFd())
			continue ;
		peer.sendMessageFrom(NickMessage(message.args[0]), message.peer);
	}
}
