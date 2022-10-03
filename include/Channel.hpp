#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include "UserManager.hpp"

class Channel
{
	public:
		Channel(const std::string &name);
		Channel(const Channel &obj);
		Channel &operator=(const Channel &rhs);
		~Channel(void);


	private:
		std::string	_name;
		unsigned int		_scope;
		UserManager			_users_in_channel;
};

#endif
