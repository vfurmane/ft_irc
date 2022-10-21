#ifndef IRCREPLIES_HPP
# define IRCREPLIES_HPP

# include "Message.hpp"
class Peer;

struct RPL_WELCOME : public Message
{
	RPL_WELCOME(Peer &peer, bool include_prefix = false);
};

struct RPL_YOURHOST : public Message
{
	RPL_YOURHOST(Peer &peer, bool include_prefix = false);
};

struct RPL_CREATED : public Message
{
	RPL_CREATED(Peer &peer, bool include_prefix = false);
};

struct RPL_MYINFO : public Message
{
	RPL_MYINFO(Peer &peer, bool include_prefix = false);
};

struct RPL_WHOISUSER : public Message
{
	RPL_WHOISUSER(Peer &peer, const Peer &target, bool include_prefix = false);
};

struct RPL_WHOISSERVER : public Message
{
	RPL_WHOISSERVER(Peer &peer, const Peer &target, Configuration &config, bool include_prefix = false);
};

struct RPL_ENDOFWHOIS : public Message
{
	RPL_ENDOFWHOIS(Peer &peer, const Peer &target, bool include_prefix = false);
};

struct RPL_WHOISCHANNELS : public Message
{
	RPL_WHOISCHANNELS(Peer &peer, const Peer &target, const std::string &list_of_channels, bool include_prefix = false);
};

struct RPL_INVITING : public Message
{
	RPL_INVITING(Peer &peer, const std::string &author_nick, const std::string &target_nick, Channel &channel, bool include_prefix = false);
};

struct RPL_NAMEREPLY : public Message
{
	RPL_NAMEREPLY(Peer &peer, const std::string &prefix, const std::string &channel, const std::string &users, bool include_prefix = false);
};

struct RPL_ENDOFNAMES : public Message
{
	RPL_ENDOFNAMES(Peer &peer, const std::string &channel, bool include_prefix = false);
};

# include "Peer.hpp"

#endif
