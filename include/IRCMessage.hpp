#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

#include <string>

struct IRCMessage
{
	IRCMessage(const std::string &input);
	IRCMessage(const IRCMessage &obj);
	IRCMessage &operator=(const IRCMessage &rhs);
	~IRCMessage(void);

	static const std::string commands_name[];
	static void(*const commands[])(void); 

	void		parse();
	void		execute();
	
	std::string		input;
	std::string		*prefix;
	std::string		command;
	std::string		arguments[15];
	size_t			argCount;
};

#endif
