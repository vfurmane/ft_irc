#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <stdint.h>

typedef enum	e_user_status
{
	CHANNEL_USER,
	CHANNEL_OPERATOR,
	CHANNEL_CREATOR
}				t_user_status;

class Channel;
class Peer;

class User
{
	public:
		User(Peer &peer, Channel &channel);
		User(const User &obj);
		User &operator=(const User &rhs);
		~User(void);

		t_user_status	getStatus(void) const;
		void	setStatus(t_user_status status);

		Peer	&peer;
		Channel	&channel;

	private:
		t_user_status	_status;
};

# include "Channel.hpp"
# include "Peer.hpp"

#endif
