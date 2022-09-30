#include "commands.hpp"
#include "IRCErrors.hpp"

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
		throw ERR_NEEDMOREPARAMS(message.command);
	if (message.peer.isRegistered())
		  throw ERR_ALREADYREGISTERED();
	if (message.arguments[1].length() != 1)
		throw ERR_UMODEUNKNOWNFLAG(); // DELETE
	if (forbidden_user_char(message.arguments[0]) == true)
		return (1);
	message.peer.registration(message.arguments[0], message.arguments[1], message.arguments[3]);
	return (1);
}
