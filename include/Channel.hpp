#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <stdint.h>
# include <string>
# include <vector>
# include "UserManager.hpp"
# include "utils.hpp"

struct Message;
class ChannelManager;

typedef enum	e_channel_namespace
{
	PUBLIC = '#'
}				t_channel_namespace;

typedef enum	e_channel_flag
{
	FLAG_INVITE = 1,
	FLAG_KEY	= 2
}				t_channel_flag;

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
		static bool					isValidName(const std::string &channel);

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

		bool	hasFlag(t_channel_flag flag) const;
		uint32_t	getFlags(void) const;
		void	setFlag(t_channel_flag flag);
		void	unsetFlag(t_channel_flag flag);
		void	setKey(const std::string &key);
		void	unsetKey(void);
		bool	compareKey(const std::string &key) const;
		void	setCreator(User &user);
		void	addInvitation(const Peer &peer);
		bool	isInvited(const Peer &peer) const;

		User	&add(Peer &peer);
		void	remove(const Peer &peer);
		void	remove(const User &user);
		void	sendMessage(const Message &message) const;

		UserManager			users;
		ChannelManager		&manager;
	private:
		std::string			_key;
		uint32_t			_flags;
		User				*_creator;
		std::vector<int>	_invitations;
};

#include "Message.hpp"
# include "ChannelManager.hpp"

#endif
