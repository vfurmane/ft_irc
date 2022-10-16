#ifndef IRCREPLIES_HPP
# define IRCREPLIES_HPP

# include "Message.hpp"
class Peer;

# define NETWORK_NAME "gibuffet"
# define SERVER_NAME "localhost" // TODO set real hostname
# define SERVER_VERSION "dev"
# define SERVER_CREATION_DATE "00:00:00 Jan 01 1970" // TODO set real date
# define AVAILABLE_USER_MODES "i" // TODO use this with MODE
# define AVAILABLE_CHANNEL_MODES "Oik" // TODO use this with MODE

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

# include "Peer.hpp"

#endif
