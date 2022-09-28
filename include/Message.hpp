#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <string>
#include "IRCErrors.hpp"

# ifndef NDEBUG
#  include <iostream>
# endif

class Peer;
class PeerManager;
struct Dependencies;

struct Message
{
	Message(Peer &peer, const std::string &input);
	Message(const Message &obj);
	Message &operator=(const Message &rhs);
	~Message(void);

	static const std::string commands_name[];
	static int(*const commands[])(Message&, Dependencies&);

	void		parse();
	int			execute(PeerManager &peers);

	const std::string	&updateInputFromFields(void);
	
	Peer			&peer;
	std::string		input;
	std::string		*prefix;
	std::string		command;
	std::string		arguments[15];
	size_t			argCount;
};

#include "Peer.hpp"
#include "PeerManager.hpp"
#include "commands.hpp"

#endif
