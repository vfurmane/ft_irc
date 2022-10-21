#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Configuration.hpp"
# include "IRCErrors.hpp"
# include "Message.hpp"
# include "Peer.hpp"
# include <stdexcept>
# include <vector>
# include <algorithm>

class	_base_channel;
class	Channel;
class	PeerManager;
class	ChannelManager;

struct ErrorMessage : public Message
{
	ErrorMessage(Peer &peer, const std::string &message, bool include_prefix = false);
};

struct	InviteMessage : public Message
{
	InviteMessage(Peer &peer, const std::string target_nick, const Channel &channel, bool include_prefix = false);
};

struct JoinMessage : public Message
{
	JoinMessage(Peer &peer, const _base_channel &channel, bool include_prefix = false);
};

struct ModeMessage : public Message
{
	ModeMessage(Peer &peer, const _base_channel &channel, const std::string flag, const std::string argument, bool include_prefix = false);
};

struct NickMessage : public Message
{
	NickMessage(Peer &peer, const std::string &new_nick, bool include_prefix = false);
};

struct PartMessage : public Message
{
	PartMessage(Peer &peer, const _base_channel &channel, const std::string &part_message, bool include_prefix = false);
};

struct KickMessage : public Message
{
	KickMessage(Peer &peer, const _base_channel &channel, const std::string target_nickname, const std::string reason, bool include_prefix = false);
};

struct PongMessage : public Message
{
	PongMessage(Peer &peer, const std::string &server_name, bool include_prefix = false);
};

struct PrivmsgMessage : public Message
{
	PrivmsgMessage(Peer &peer, const std::string &target, const std::string &text_to_send, bool include_prefix = false);
};

struct QuitMessage : public Message
{
	QuitMessage(Peer &peer, const std::string &quit_message, bool include_prefix = false);
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
int	command_invite(Message &message, Dependencies &deps);
int	command_join(Message &message, Dependencies &deps);
int	command_kick(Message &message, Dependencies &deps);
int	command_mode(Message &message, Dependencies &deps);
int	command_names(Message &message, Dependencies &deps);
int	command_nick(Message &message, Dependencies &deps);
int	command_notice(Message &message, Dependencies &deps);
int	command_part(Message &message, Dependencies &deps);
int	command_pass(Message &message, Dependencies &deps);
int	command_ping(Message &message, Dependencies &deps);
int	command_privmsg(Message &message, Dependencies &deps);
int	command_quit(Message &message, Dependencies &deps);
int	command_user(Message &message, Dependencies &deps);
int	command_whois(Message &message, Dependencies &deps);

void	command_mode_channel(Message &message, Dependencies &deps, const _base_channel &base_channel);
void	flag_operator(bool add_flag, User &author, Channel &channel, const std::string &argument);
void	flag_invite_only(bool add_flag, User &author, Channel &channel, const std::string &argument);
void	flag_key(bool add_flag, User &author, Channel &channel, const std::string &argument);

void	command_privmsg_channel(Dependencies &deps, Peer &peer, const _base_channel &base_channel, const std::string text_to_send);
void	command_privmsg_nickname(Dependencies &deps, Peer &peer, const std::string &nickname, const std::string text_to_send);

void	command_notice_channel(Dependencies &deps, Peer &peer, const _base_channel &base_channel, const std::string text_to_send);
void	command_notice_nickname(Dependencies &deps, Peer &peer, const std::string &nickname, const std::string text_to_send);

# include "Channel.hpp"
# include "PeerManager.hpp"
# include "ChannelManager.hpp"

#endif
