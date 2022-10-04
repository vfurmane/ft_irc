#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <stdint.h>
# include <string>
# include "UserManager.hpp"

class Channel
{
	public:
		Channel(const std::string &name);
		Channel(const Channel &obj);
		Channel &operator=(const Channel &rhs);
		~Channel(void);


	private:
		const std::string	_name;
		uint32_t			_flags;
		UserManager			_users;
};

#endif
