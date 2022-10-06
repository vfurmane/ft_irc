#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <stdint.h>
# include <string>
# include "UserManager.hpp"

class _base_channel
{
	public:
		_base_channel(const std::string &name);
		_base_channel(const _base_channel &obj);
		_base_channel &operator=(const _base_channel &rhs);
		~_base_channel(void);

		const std::string	&getName(void) const;

	protected:
		const std::string	_name;
};

class Channel : public _base_channel
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
		std::string			_key;
		uint32_t			_flags;
		UserManager			_users;
};

#endif
