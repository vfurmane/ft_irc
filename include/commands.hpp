#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Configuration.hpp"
# include "IRCErrors.hpp"
# include "Message.hpp"
# include "Peer.hpp"

class	PeerManager;
class	ChannelManager;

struct ErrorMessage : public Message
{
	ErrorMessage(Peer &peer, const std::string &message, bool include_prefix = false);
};

struct NickMessage : public Message
{
	NickMessage(Peer &peer, const std::string &new_nick, bool include_prefix = false);
};

struct Dependencies
{
	Configuration	&config;
	PeerManager	&peers;
	ChannelManager	&channels;
};

int	command_nick(Message &message, Dependencies &deps);
int	command_quit(Message &message, Dependencies &deps);
int	command_user(Message &message, Dependencies &deps);
int	command_pass(Message &message, Dependencies &deps);

# include "PeerManager.hpp"
# include "ChannelManager.hpp"

#endif
