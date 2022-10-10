#include "commands.hpp"
#include "Channel.hpp"
#include <algorithm>
#include <vector>

int command_part(Message &message, Dependencies &deps)
{
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS("PART");

	std::vector<std::string> channels = parseList(message.arguments[0]);
	std::vector<std::string>::const_iterator channel_it = channels.begin();
	while (channel_it != channels.end())
	{
		std::vector<std::string>::const_iterator res = std::find(channels.begin(), channels.end(), *channel_it);
		if (res == channels.end())
			throw ERR_NOSUCHCHANNEL(*channel_it);
		else 
		{
			Channel &channel = deps.channels[*channel_it];
			
			if (channel.users.has(message.peer.getUsername()) == true)
				channel.remove(channel.users[message.peer.getUsername()]);
			else
				throw ERR_NOTONCHANNEL(*channel_it);
		}
		++channel_it;
	}
	return 1;
}

