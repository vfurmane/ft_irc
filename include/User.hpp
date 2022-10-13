#ifndef USER_HPP
# define USER_HPP

# include <string>

typedef enum	e_user_flag
{
	 CHANNEL_USER,
	 CHANNEL_OPERATOR,
	 CHANNEL_CREATOR
}				t_user_flag;

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
		t_user_flag	flags;
};

# include "Channel.hpp"
# include "Peer.hpp"

#endif
