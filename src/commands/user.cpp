#include "commands.hpp"
#include "IRCErrors.hpp"

int	command_user(Message &message, Dependencies &deps)
{
	(void)deps;
	if (message.argCount < 4)
		throw ERR_NEEDMOREPARAMS(message.command);
	if (message.peer.isRegistered())
		  throw ERR_ALREADYREGISTERED();
	if (message.arguments[1].length() != 1)
		throw ERR_UMODEUNKNOWNFLAG(); // DELETE
	message.peer.registration(message.arguments[0], message.arguments[1], message.arguments[3]);
	return 1;
}
