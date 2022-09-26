#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "IRCMessage.hpp"
# include "IRCPeer.hpp"

struct ErrorMessage : public IRCMessage
{
	ErrorMessage(IRCPeer &peer, const std::string &quit_message);
};

#endif
