#include "commands.hpp"

static void	list_all_channels(Message &message, Dependencies &deps)
{
	for (ChannelManager::iterator chan_it = deps.channels.begin(); chan_it != deps.channels.end(); ++chan_it)
	{
		message.peer.sendMessage(RPL_LIST(message.peer, chan_it->second.stringify(), chan_it->second.getTopic()));
	}
}

int	command_list(Message &message, Dependencies &deps)
{
	if (message.argCount < 1 || message.arguments[0].empty())
		list_all_channels(message, deps);
	else
	{
		std::vector<std::string> channels = parseList(message.arguments[0]);
		std::vector<std::string>::const_iterator channel_it = channels.begin();

		while (channel_it != channels.end())
		{
			if (_base_channel::isValidName(*channel_it))
			{
				_base_channel base_channel = Channel::parse(*channel_it);
				if (deps.channels.has(base_channel.getName()))
				{
					Channel &channel = deps.channels[base_channel.getName()];
					message.peer.sendMessage(RPL_LIST(message.peer, channel.stringify(), channel.getTopic()));
				}
			}
			++channel_it;
		}
	}
	message.peer.sendMessage(RPL_LISTEND(message.peer, false));
	return 1;
}
