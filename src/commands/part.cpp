#include "commands.hpp"

int command_part(Message &message, Dependencies &deps)
{
	if (message.argCount < 1 || message.arguments[0].empty())
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), "PART");

	std::vector<std::string> channels = parseList(message.arguments[0]);
	std::vector<std::string>::const_iterator channel_it = channels.begin();

	ChannelManager &channel_manager = deps.channels;

	while (channel_it != channels.end())
	{
		if (_base_channel::isValidName(*channel_it))
		{
			_base_channel base_channel = Channel::parse(*channel_it);
			if (!channel_manager.has(base_channel.getName()))
				message.peer.sendMessage(ERR_NOSUCHCHANNEL(message.peer.getNickname(), *channel_it));
			else 
			{
				Channel &channel = deps.channels[base_channel.getName()];
				if (channel.users.has(message.peer.getFd()))
				{
					message.peer.sendMessage(PartMessage(message.peer, channel, message.arguments[1], true));
					channel.sendMessage(PartMessage(message.peer, channel, message.arguments[1], false));
					channel.remove(channel.users[message.peer.getFd()]);
				}
				else
					message.peer.sendMessage(ERR_NOTONCHANNEL(message.peer.getNickname(), *channel_it));
			}
		}
		else
			message.peer.sendMessage(ERR_NOSUCHCHANNEL(message.peer.getNickname(), *channel_it));
		++channel_it;
	}
	return 1;
}
