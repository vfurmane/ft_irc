#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	command_mode_channel(Message &message, Dependencies &deps, std::string &channel_name);

int	command_mode(Message &message, Dependencies &deps)
{
	if (message.argCount < 2)
		throw ERR_NEEDMOREPARAMS(message.command);
	std::string channel_name;
	try
	{
		channel_name = _base_channel::parse(message.arguments[0]).getName();
	} 
	catch (std::exception &e)
	{
		return (1);
	}
	if (!deps.channels.has(channel_name))
		return (1);
	if (!deps.channels.get(channel_name).users.has(message.peer.getUsername()))
		return (1);
	command_mode_channel(message, deps, channel_name);
	return (1);
}
