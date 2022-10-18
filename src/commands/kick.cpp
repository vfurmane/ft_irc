#include "commands.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"

int	command_kick(Message &message, Dependencies &deps)
{
	if (message.argCount < 2)
		throw ERR_NEEDMOREPARAMS("KICK");
	if (!_base_channel::isValidName(message.arguments[0]))
		return (1);
	_base_channel base_channel = _base_channel::parse(message.arguments[0]);
	if (!deps.channels.has(base_channel))
		ERR_NOSUCHCHANNEL(message.arguments[0]);
	Channel	&channel = deps.channels.get(base_channel.getName());
	User	&author = channel.users.getByNickname(message.peer.getNickname());
	User	&target = channel.users.getByNickname(message.arguments[1]);
	if (!channel.users.hasByNickname(author.peer.getNickname()))
		throw ERR_NOTONCHANNEL(channel.getName());
	if (!channel.users.has(target.peer.getNickname()))
		throw ERR_USERNOTINCHANNEL(target.peer.getNickname(), channel.getName());
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(channel.getName());
	if (author.getStatus() < target.getStatus())
		return (1);
	channel.sendMessage(KickMessage(message.peer, target.peer.getNickname(), base_channel, author.peer.getNickname(), message.arguments[2]));
	channel.remove(target);
	return (1);
}
