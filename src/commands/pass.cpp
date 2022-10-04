#include "IRCErrors.hpp"
#include "commands.hpp"

int	command_pass(Message &message, Dependencies &deps)
{
	const std::string	&password = message.arguments[0];

	if (deps.config.getPassword().empty())
		return (1);
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS(message.command);
	if (message.peer.isRegistered())
		throw ERR_ALREADYREGISTRED();
	message.peer.setPassword(password);	
	return (1);
}
