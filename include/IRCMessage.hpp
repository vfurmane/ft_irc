#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

#include <string>

class IRCMessage
{
	public:

	IRCMessage(const std::string &input);

	static const std::string commands_name[];
	static void(*const commands[])(void); 

	void		parse();
	void		execute();
	
	private:

	void	_parseArguments(std::string::const_iterator &it);

	std::string		_input;
	std::string		*_prefix;
	std::string		_command;
	std::string		_arguments[15];
	size_t			_argCount;
};

#endif
