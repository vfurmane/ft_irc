#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <stdint.h>
# include <string>
# include "UserManager.hpp"
# include "utils.hpp"

struct Message;
class ChannelManager;

typedef enum	e_channel_namespace
{
	PUBLIC = '#'
}				t_channel_namespace;

class _base_channel
{
	public:
		_base_channel(const std::string &name);
		_base_channel(const _base_channel &obj);
		_base_channel &operator=(const _base_channel &rhs);
		~_base_channel(void);

		const std::string			&getName(void) const;
		const t_channel_namespace	&getNamespace(void) const;
		std::string					stringify(void) const;

		static _base_channel		parse(const std::string &channel);

	protected:
		const std::string			_name;
		const t_channel_namespace	_namespace;
};

class Channel : public _base_channel
{
	public:
		Channel(ChannelManager &manager, const std::string &name);
		Channel(ChannelManager &manager, const _base_channel &obj);
		Channel(const Channel &obj);
		Channel &operator=(const Channel &rhs);
		~Channel(void);

		void	setKey(const std::string &key);
		void	unsetKey(void);
		bool	compareKey(const std::string &key) const;
		void	setCreator(User &user);

		User	&add(Peer &peer);
		void	remove(const User &user);
		void	sendMessage(const Message &message) const;

		UserManager			users;
		ChannelManager		&manager;
	private:
		std::string			_key;
		uint32_t			_flags;
		User				*_creator;
};

#include "Message.hpp"
# include "ChannelManager.hpp"

#endif
