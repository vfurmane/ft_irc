#include "commands.hpp"
#include "IRCErrors.hpp"

void	command_user(IRCMessage &message, Dependencies &deps)
{
	if (message.getArgsCount() < 4)
		throw ERR_NEEDMOREPARAMS(message.getCommand());
	if (message.peer.isRegistered())
		  throw ERR_ALREADYREGISTERED();
	std::size_t pos;
	int mode = stoi(message.getArguments[1], &pos, 10);
	message.peer.registeration(message.getArguments()[0], mode, message.getArguments()[3]);
}
