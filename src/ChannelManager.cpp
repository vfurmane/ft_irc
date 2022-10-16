#include "ChannelManager.hpp"

ChannelManager::ChannelManager(): Manager()
{

}

ChannelManager::ChannelManager(const ChannelManager &obj) : Manager(obj)
{
}

ChannelManager &ChannelManager::operator=(const ChannelManager &rhs)
{
	(void)rhs;
	return *this;
}

Channel	&ChannelManager::operator[](const std::string &name)
{
	const std::string	lowercase_name = toIRCLower(name);
	return Manager::operator[](lowercase_name);
}

ChannelManager::~ChannelManager()
{

}

Channel	&ChannelManager::add(const std::string &name)
{
	_base_channel	base_channel(name);
	return this->add(base_channel);
}

Channel	&ChannelManager::add(const _base_channel &base_channel)
{
	return Manager::add(base_channel.getName(), Channel(*this, base_channel));
}

void ChannelManager::remove(const std::string &name)
{
	const std::string	lowercase_name = toIRCLower(name);
	Manager::remove(lowercase_name);
}

bool	ChannelManager::has(const std::string &name) const
{
	const std::string	lowercase_name = toIRCLower(name);
	return Manager::has(lowercase_name);
}

bool	ChannelManager::has(const _base_channel &base_channel) const
{
	return this->has(base_channel.getName());
}
