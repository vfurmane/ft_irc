#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "IRCErrors.hpp"
# include "Message.hpp"
# include "Peer.hpp"
# include "PeerManager.hpp"

struct ErrorMessage : public Message
{
	ErrorMessage(Peer &peer, const std::string &quit_message);
};

struct Dependencies
{
	PeerManager	&peers;
};

struct NickMessage : public Message
{
	NickMessage(Peer &peer, const std::string &new_nick);
};

void	command_nick(Message &message, Dependencies &deps);
void	command_quit(Message &message, Dependencies &deps);
void	command_user(Message &message, Dependencies &deps);

#endif
