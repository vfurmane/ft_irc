#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "IRCMessage.hpp"
# include "IRCPeer.hpp"

struct QuitMessage : public IRCMessage
{
	ErrorMessage(IRCPeer &peer, const std::string &quit_message);
};

#endif
