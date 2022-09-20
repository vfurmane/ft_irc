#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

#include <string>

class IRCMessage
{
	public:

	IRCMessage(const std::string &input);
	
	void	parse();

	private:

	void	parseArguments(std::string::const_iterator &it);

	std::string		_input;
	std::string		*_prefix;
	std::string		_command;
	std::string		_arguments[15];
	size_t			_argCount;
};

#endif
