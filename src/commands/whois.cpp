#include "commands.hpp"

int	command_whois(Message &message, Dependencies &deps)
{
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), "WHOIS");
	if (!deps.peers.hasByNickname(message.arguments[0]))
		 message.peer.sendMessage(ERR_NOSUCHNICK(message.arguments[0]));
	else
	{
		std::string	list_of_channels;
		Peer	&target = deps.peers.getByNickname(message.arguments[0]);
		ChannelManager::const_iterator	it = deps.channels.begin();
		while (it != deps.channels.end())
		{
			list_of_channels += it->second.stringify();
			++it;
			if (it != deps.channels.end())
				list_of_channels += " ";
		}
		message.peer.sendMessage(RPL_WHOISUSER(message.peer, target));
		message.peer.sendMessage(RPL_WHOISCHANNELS(message.peer, target, list_of_channels));
		message.peer.sendMessage(RPL_WHOISSERVER(message.peer, target, deps.config));
	}
	message.peer.sendMessage(RPL_ENDOFWHOIS(message.peer, message.arguments[0]));
	return (1);
}
