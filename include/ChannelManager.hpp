#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

// # include "Channel.hpp"
# include <map>
# include <string>
#include <utility>
// # include <algorithm>

class ChannelManager
{
	public:
		typedef std::map<std::string, Channel>::iterator		iterator;
		typedef std::map<std::string, Channel>::const_iterator	const_iterator;
		
		ChannelManager();
		ChannelManager(const ChannelManager &obj);
		ChannelManager &operator=(const ChannelManager &rhs);
		~ChannelManager();

		ChannelManager &operator[](std::string name);
			
		iterator		begin(void);
		iterator		end(void);
		const_iterator	begin(void) const;
		const_iterator	end(void) const;
		std::pair<ChannelManager::iterator, bool>	add(std::string name);
		void			remove(std::string name);
	
	private:
		std::map<std::string, Channel>	_channels;	
};

#endif
