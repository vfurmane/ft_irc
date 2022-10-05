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

		void	setKey(const std::string &key);
		void	unsetKey(void);
		bool	compareKey(const std::string &key) const;
	private:
		const std::string	_name;
		std::string			_key;
		uint32_t			_flags;
		UserManager			_users;
};

#endif
