#ifndef IRCMESSAGESTREAM_HPP
# define IRCMESSAGESTREAM_HPP

#include <string>

class IRCMessageStream
{
	public:

	IRCMessageStream(const std::string &input);
	
	void	parse();

	private:

	void	parseArguments(std::string::const_iterator &it);

	std::string		_input;
	std::string		*_prefix;
	std::string		_command;
	std::string		_arguments[15];
	int				_argCount;
};

#endif
