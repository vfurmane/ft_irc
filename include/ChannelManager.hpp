#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

# include <map>
# include <string>

class _base_channel;
class Channel;

class ChannelManager
{
	public:
		typedef std::map<std::string, Channel>::iterator		iterator;
		typedef std::map<std::string, Channel>::const_iterator	const_iterator;
		
		ChannelManager();
		ChannelManager(const ChannelManager &obj);
		ChannelManager &operator=(const ChannelManager &rhs);
		~ChannelManager();

		Channel &operator[](const std::string &name);
			
		iterator		begin(void);
		iterator		end(void);
		const_iterator	begin(void) const;
		const_iterator	end(void) const;
		std::pair<ChannelManager::iterator, bool>	add(const std::string &name);
		std::pair<ChannelManager::iterator, bool>	add(const _base_channel &base_channel);
		void			remove(const std::string &name);
		bool			has(const std::string &name) const;
	
	private:
		std::map<std::string, Channel>	_channels;	
};

# include "Channel.hpp"

#endif
