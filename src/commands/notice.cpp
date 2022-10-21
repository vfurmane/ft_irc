#include "commands.hpp"

int command_notice(Message &message, Dependencies &deps)
{
	if (message.argCount < 2 || message.arguments[1].empty())
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), message.command);

	const std::vector<std::string>	targets = parseList(message.arguments[0]);
	const std::string				&text_to_send = message.arguments[1];
	
	std::vector<std::string>::const_iterator	it = targets.begin();
	while (it != targets.end())
	{
#ifndef NDEBUG
		std::cerr << "Sending a notice to " << *it << std::endl;
#endif
		if (_base_channel::isValidName(*it))
		{
#ifndef NDEBUG
			std::cerr << "Found out it is a channel" << std::endl;
#endif
			const _base_channel base_channel = _base_channel::parse(*it);
			command_notice_channel(deps, message.peer, base_channel, text_to_send);
		}
		else
		{
#ifndef NDEBUG
			std::cerr << "Found out it is a nickname" << std::endl;
#endif
			command_notice_nickname(deps, message.peer, *it, text_to_send);

		}
		++it;
	}
	return 1;
}
