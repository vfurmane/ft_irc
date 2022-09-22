#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "IRCErrors.hpp"
# include "IRCMessage.hpp"
# include "IRCPeer.hpp"
# include "IRCPeerManager.hpp"

struct ErrorMessage : public IRCMessage
{
	ErrorMessage(IRCPeer &peer, const std::string &quit_message);
};

struct Dependencies
{
	IRCPeerManager	&peers;
};

struct NickMessage : public IRCMessage
{
	NickMessage(IRCPeer &peer, const std::string &new_nick);
};

void	command_nick(IRCMessage &message, Dependencies &deps);

#endif
