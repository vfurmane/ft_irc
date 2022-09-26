#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <string>
#include "IRCErrors.hpp"

# ifndef NDEBUG
#  include <iostream>
# endif

struct Message
{
	Message(const std::string &input);
	Message(const Message &obj);
	Message &operator=(const Message &rhs);
	~Message(void);

	static const std::string commands_name[];
	static void(*const commands[])(void); 

	void		parse();
	void		execute();

	size_t				getArgsCount(void) const;
	const std::string	*getArguments(void) const;
	const std::string	&getInput(void) const;
	const std::string	&updateInputFromFields(void);

	std::string		input;
	std::string		*prefix;
	std::string		command;
	std::string		arguments[15];
	size_t			argCount;
};

#endif
