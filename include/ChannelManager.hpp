#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include "Manager.hpp"
# include "utils.hpp"
# include <string>

class _base_channel;
class Channel;

class ChannelManager : public Manager<std::string, Channel>
{
	public:
		ChannelManager();
		ChannelManager(const ChannelManager &obj);
		ChannelManager &operator=(const ChannelManager &rhs);
		~ChannelManager();

		Channel			&operator[](const std::string &name);

		Channel			&add(const std::string &name);
		Channel			&add(const _base_channel &base_channel);
		void			remove(const std::string &name);
		Channel			&get(const std::string &name);
		Channel			&get(const _base_channel &base_channel);
		bool			has(const std::string &name) const;
		bool			has(const _base_channel &base_channel) const;
};

# include "Channel.hpp"

#endif
