#include "commands.hpp"

static bool	forbidden_user_char(const std::string &user)
{
	static const std::string forbidden = "@\r\n ";

	for (std::string::const_iterator it = user.begin(); it != user.end(); ++it)
	{
		if (forbidden.find(*it) != std::string::npos || (*it) == '\0')
			return (true);
	}
	return (false);
}

int	command_user(Message &message, Dependencies &deps)
{
	(void)deps;
	if (message.argCount < 4)
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), message.command);
	if (message.peer.isRegistered())
		throw ERR_ALREADYREGISTRED(message.peer.getNickname());
	if (forbidden_user_char(message.arguments[0]) == true)
		return (1);
	message.peer.setUsername(message.arguments[0]);
	message.peer.setRealName(message.arguments[3]);
	if (message.peer.hasAllFields())
	{
		if (message.peer.registration() == 0)
			return 0;
	}
	return (1);
}
