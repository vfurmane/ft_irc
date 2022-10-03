#include "ChannelManager.hpp"

ChannelManager::ChannelManager(): _channels()
{

}

ChannelManager::ChannelManager(const ChannelManager &obj)
{
	this->_channels = obj._channels;	
}

ChannelManager &ChannelManager::operator=(const ChannelManager &rhs)
{
	this->_channels = rhs._channels;
	return *this;
}

ChannelManager &ChannelManager::operator[](std::string name)
{
	return this->_channels.at(name);
}

ChannelManager::iterator ChannelManager::begin()
{
	return this->_channels.begin();
}

ChannelManager::iterator ChannelManager::end()
{
	return this->_channels.end();
}

ChannelManager::const_iterator ChannelManager::begin() const
{
	return this->_channels.begin();
}

ChannelManager::const_iterator ChannelManager::end() const
{
	return this->_channels.end();
}

std::pair<ChannelManager::iterator, bool> ChannelManager::add(std::string name)
{
	return this->_channels.insert(std::make_pair(name, Channel(name)));
}

void ChannelManager::remove(std::string name)
{
	this->_channels.erase(name);
}
