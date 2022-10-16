#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Configuration.hpp"
# include "IRCErrors.hpp"
# include "Message.hpp"
# include "Peer.hpp"
# include <stdexcept>
# include <vector>

class	_base_channel;
class	Channel;
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

struct JoinMessage : public Message
{
	JoinMessage(Peer &peer, const _base_channel &channel, bool include_prefix = false);
};

struct PongMessage : public Message
{
	PongMessage(Peer &peer, const std::string &server_name, bool include_prefix = false);
};

struct Dependencies
{
	Configuration	&config;
	PeerManager	&peers;
	ChannelManager	&channels;
};

_base_channel				parseChannel(const std::string &channel);
std::vector<std::string>	parseList(const std::string &list);

int	command_cap(Message &message, Dependencies &deps);
int	command_join(Message &message, Dependencies &deps);
int	command_mode(Message &message, Dependencies &deps);
int	command_nick(Message &message, Dependencies &deps);
int	command_part(Message &message, Dependencies &deps);
int	command_pass(Message &message, Dependencies &deps);
int	command_ping(Message &message, Dependencies &deps);
int	command_quit(Message &message, Dependencies &deps);
int	command_user(Message &message, Dependencies &deps);

void	command_mode_channel(Message &message, Dependencies &deps, const _base_channel &base_channel);
void	flag_operator(bool add_flag, User &author, Channel &channel, const std::string &argument);
void	flag_invite_only(bool add_flag, User &author, Channel &channel, const std::string &argument);
void	flag_key(bool add_flag, User &author, Channel &channel, const std::string &argument);

# include "Channel.hpp"
# include "PeerManager.hpp"
# include "ChannelManager.hpp"

#endif
