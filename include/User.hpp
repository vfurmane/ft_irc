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

		uint8_t	getStatus(void) const;
		void	setStatus(uint8_t status);

		Peer	&peer;
		Channel	&channel;

	private:
		uint8_t	_status;
};

# include "Channel.hpp"
# include "Peer.hpp"

#endif
