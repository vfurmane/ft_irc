#include "../include/executeCMD.hpp"
#include <iostream>

void	executeCommand(IRCMessage &message)
{
	std::string		commands_name[] = {};
	typedef void	(*t_command)(void);

	t_command commands[] = {};

	for (int i = 0; i < 4; i++) {
		if (commands_name[i] == message.getCommand()) {
			commands[i]();
		}
	}
}
