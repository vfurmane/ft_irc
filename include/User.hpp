#ifndef USER_HPP
# define USER_HPP

# include <string>

class Channel;
class Peer;

class User
{
	public:
		User(Peer &peer, Channel &channel);
		User(const User &obj);
		User &operator=(const User &rhs);
		~User(void);

		Peer	&peer;
		Channel	&channel;
};

# include "Channel.hpp"
# include "Peer.hpp"

#endif
