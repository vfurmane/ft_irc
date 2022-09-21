#include "../include/executeCMD.hpp"
#include <iostream>

void	execute_cmd(std::string command_to_execute)
{
	std::string		cmd_list[4];
	typedef void	(*cmdToExec)(void);

	cmdToExec CmdPointer[4] = {
		// &command_connect,
		// &command_nick,
		// &command_join,
		// &command_query
	};

	cmd_list[0] = "CONNECT";
	cmd_list[1] = "NICK";
	cmd_list[2] = "JOIN";
	cmd_list[3] = "QUERY";

	for (int i = 0; i < 4; i++) {
		if (cmd_list[i] == command_to_execute) {
			CmdPointer[i]();
		}
	}
}

