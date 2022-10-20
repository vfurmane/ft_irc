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

struct RPL_INVITING : public Message
{
	RPL_INVITING(Peer &peer, const std::string &author_nick, const std::string &target_nick, Channel &channel, bool include_prefix = false);
};

# include "Peer.hpp"

#endif
