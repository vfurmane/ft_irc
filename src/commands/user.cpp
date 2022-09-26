#include "commands.hpp"
#include "IRCErrors.hpp"

void	command_user(IRCMessage &message, Dependencies &deps)
{
	if (message.getArgsCount() < 4)
		throw ERR_NEEDMOREPARAMS(message.getCommand());
	if (message.peer.isRegistered())
		  throw ERR_ALREADYREGISTERED();
	if (message.peer.getArguments()[1].length() != 1)
		throw ERR_UMODEUNKNOWNFLAG(); // DELETE
	message.peer.registeration(message.getArguments()[0], message.getArguments()[1], message.getArguments()[3]);
}
