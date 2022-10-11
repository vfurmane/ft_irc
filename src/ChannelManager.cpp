#include "ChannelManager.hpp"
#include "utils.hpp"
#include <utility>

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

ChannelManager::~ChannelManager()
{

}

Channel &ChannelManager::operator[](const std::string &name)
{
	const std::string	lowercase_name = toIRCLower(name);
	return this->_channels.at(lowercase_name);
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

std::pair<ChannelManager::iterator, bool> ChannelManager::add(const std::string &name)
{
	_base_channel	base_channel(name);
	return this->add(base_channel);
}

std::pair<ChannelManager::iterator, bool>	ChannelManager::add(const _base_channel &base_channel)
{
	return this->_channels.insert(std::make_pair(base_channel.getName(), base_channel));
}

void ChannelManager::remove(const std::string &name)
{
	const std::string	lowercase_name = toIRCLower(name);
	this->_channels.erase(lowercase_name);
}

bool	ChannelManager::has(const std::string &name) const
{
	return this->_channels.find(name) != this->_channels.end();
}
