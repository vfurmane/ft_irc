#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "IRCMessage.hpp"
# include "IRCPeer.hpp"

struct QuitMessage : public IRCMessage
{
	QuitMessage(IRCPeer &peer, const std::string &quit_message);
};

#endif
