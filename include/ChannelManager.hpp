#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include "Manager.hpp"
# include "utils.hpp"
# include <map>
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

		Channel			&add(const std::string &name);
		Channel			&add(const _base_channel &base_channel);
		void			remove(const std::string &name);
};

# include "Channel.hpp"

#endif
