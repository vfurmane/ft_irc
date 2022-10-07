#ifndef USER_HPP
# define USER_HPP

# include <string>
# include "Peer.hpp"

class User
{
	public:
		User(Peer &peer);
		User(const User &obj);
		User &operator=(const User &rhs);
		~User(void);

		Peer	&peer;
};

#endif
