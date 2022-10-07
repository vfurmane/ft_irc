#include "commands.hpp"

int		command_join(Message &message, Dependencies &deps)
{
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS("JOIN");

	const std::vector<std::string>	channels = parseList(message.arguments[0]);
	const std::vector<std::string>	keys = message.argCount >= 2 ?
		parseList(message.arguments[1]) : std::vector<std::string>();
	
	std::vector<std::string>::const_iterator	chan_it = channels.begin();
	std::vector<std::string>::const_iterator	key_it = keys.begin();
	while (chan_it != channels.end())
	{
		_base_channel base_channel = parseChannel(*chan_it);
		try
		{
			Channel	&channel = deps.channels[base_channel.getName()];
			if (key_it != keys.end() && !channel.compareKey(*key_it))
				message.peer.sendMessage(ERR_BADCHANNELKEY(*chan_it));
			else
			{
				channel.add(message.peer);
				message.peer.sendMessage(JoinMessage(message.peer, base_channel));
			}
		}
		catch (std::out_of_range &)
		{
			message.peer.createChannel(base_channel);
			message.peer.sendMessage(JoinMessage(message.peer, base_channel));
		}
		++chan_it;
		if (key_it != keys.end())
			++key_it;
	}
	return 1;
}
