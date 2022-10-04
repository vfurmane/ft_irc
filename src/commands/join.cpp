#include "commands.hpp"

int		command_join(Message &message, Dependencies &deps)
{
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS("JOIN");

	const std::vector<std::string>	channels = parseList(message.arguments[0]);
	const std::vector<std::string>	keys = message.argCount >= 2 ?
		parseList(message.arguments[1]) : std::vector<std::string>();

	if (!keys.empty() && keys.size() != channels.size())
		throw ERR_NEEDMOREPARAMS("JOIN");
	
	std::vector<std::string>::const_iterator	chan_it = channels.begin();
	std::vector<std::string>::const_iterator	key_it = keys.begin();
	while (chan_it != channels.end())
	{
		Channel	&channel = deps.channels.get(*chan_it);
		if (!keys.empty() && channel.comparePassword(*key_it))
			message.peer.sendMessage(ERR_BADCHANNELKEY(*chan_it));
		else
			channel.add(message.peer);
		++chan_it;
		if (!keys.empty())
			++key_it;
	}
	return 1;
}
