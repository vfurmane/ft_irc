#include "IRCErrors.hpp"
#include "commands.hpp"

int	command_pass(Message &message, Dependencies &deps)
{
	const std::string	&password = message.arguments[0];

	if (!deps.config.getPassword().empty())
	{
		if (message.argCount < 1)
			throw ERR_NEEDMOREPARAMS(message.command);
		if (message.peer.isLogged())
			throw ERR_ALREADYREGISTERED();
	}
	if (password == deps.config.getPassword())
		message.peer.login();
	return (1);
}
