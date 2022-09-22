#ifndef IRCMESSAGE_HPP
# define IRCMESSAGE_HPP

#include <string>

class IRCPeer;

class IRCMessage
{
	public:

	IRCMessage(IRCPeer &peer, const std::string &input);
	IRCMessage(const IRCMessage &obj);
	IRCMessage &operator=(const IRCMessage &rhs);
	~IRCMessage(void);

	static const std::string commands_name[];
	static void(*const commands[])(void); 

	void		parse();
	void		execute();
	private:
	
	size_t	getArgsCount(void) const;
	const std::string	*getArguments(void) const;
	const std::string	&getInput(void) const;

	IRCPeer	&peer;

	protected:

	void				_parseArguments(std::string::const_iterator &it);
	const std::string	&_updateInputFromFields(void);

	std::string		_input;
	std::string		*_prefix;
	std::string		_command;
	std::string		_arguments[15];
	size_t			_argCount;
};

# include "IRCPeer.hpp"

#endif
