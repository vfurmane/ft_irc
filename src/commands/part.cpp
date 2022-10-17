#include "commands.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"
#include <algorithm>
#include <vector>

int command_part(Message &message, Dependencies &deps)
{
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS("PART");

	std::vector<std::string> channels = parseList(message.arguments[0]);
	std::vector<std::string>::const_iterator channel_it = channels.begin();

	ChannelManager &channel_manager = deps.channels;

	while (channel_it != channels.end())
	{
		if (!_base_channel::isValidName(*channel_it))
		{
			message.peer.sendMessage(ERR_NOSUCHCHANNEL(*channel_it));
			++channel_it;
		}
		_base_channel base_channel = Channel::parse(*channel_it);
		if (!channel_manager.has(base_channel.getName()))
			message.peer.sendMessage(ERR_NOSUCHCHANNEL(*channel_it));
		else 
		{
			Channel &channel = deps.channels[base_channel.getName()];
			if (channel.users.has(message.peer.getUsername()))
			{
				channel.remove(channel.users[message.peer.getUsername()]);
				if (!message.arguments[1].empty())
				{
					Message reply(message.peer, message.arguments[1]);
					channel.sendMessage(reply);
				}
			}
			else
				message.peer.sendMessage(ERR_NOTONCHANNEL(*channel_it));
		}
		++channel_it;
	}
	return 1;
}

