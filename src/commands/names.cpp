#include "commands.hpp"

int	command_names(Message &message, Dependencies &deps)
{
	if (message.argCount < 1 || message.arguments[0].empty())
		message.peer.sendMessage(RPL_ENDOFNAMES(message.peer, "*", false));
	else
	{
		std::vector<std::string>	channels = parseList(message.arguments[0]);

		std::vector<std::string>::const_iterator	chan_it = channels.begin();
		std::string	users_list;
		while (chan_it != channels.end())
		{
			if (_base_channel::isValidName(*chan_it))
			{
				_base_channel base_channel = Channel::parse(*chan_it);
				if (deps.channels.has(base_channel.getName()))
				{
					Channel &channel = deps.channels[base_channel.getName()];
					UserManager::iterator	user_it = channel.users.begin();
					while (user_it != channel.users.end())
					{
						if (user_it->second.getStatus() == CHANNEL_CREATOR)
							users_list += "@" + user_it->second.peer.getNickname();
						else
							users_list += user_it->second.peer.getNickname();
						++user_it;
						if (user_it != channel.users.end())
							users_list += " ";
					}
					message.peer.sendMessage(RPL_NAMEREPLY(message.peer, "=", channel.stringify(), users_list, false));
					users_list.clear();
				}
			}
			message.peer.sendMessage(RPL_ENDOFNAMES(message.peer, *chan_it, false));
			++chan_it;
		}
	}
	return (1);
}
