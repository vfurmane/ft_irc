#include "commands.hpp"

static void	kick_user(Message &message, _base_channel &base_channel, Channel &channel, User &author, User &target)
{
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(message.peer.getNickname(), channel.stringify());
	if (author.getStatus() < target.getStatus())
		return ;
	message.peer.sendMessage(KickMessage(message.peer, base_channel, target.peer.getNickname(), message.arguments[2], true));
	channel.sendMessage(KickMessage(message.peer, base_channel, target.peer.getNickname(), message.arguments[2]));
	channel.remove(target);
}

int	command_kick(Message &message, Dependencies &deps)
{
	if (message.argCount < 2 || message.arguments[0].empty() || message.arguments[1].empty())
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), "KICK");

	if (!_base_channel::isValidName(message.arguments[0]))
		return (1);
	_base_channel base_channel = _base_channel::parse(message.arguments[0]);
	if (!deps.channels.has(base_channel))
		throw ERR_NOSUCHCHANNEL(message.peer.getNickname(), message.arguments[0]);
	Channel	&channel = deps.channels.get(base_channel.getName());
	if (!channel.users.hasByNickname(message.peer.getNickname()))
		throw ERR_NOTONCHANNEL(message.peer.getNickname(), channel.getName());
	User	&author = channel.users.getByNickname(message.peer.getNickname());
	if (!channel.users.hasByNickname(message.arguments[1]))
		throw ERR_USERNOTINCHANNEL(message.peer.getNickname(), message.arguments[1], channel.getName());
	User	&target = channel.users.getByNickname(message.arguments[1]);
	kick_user(message, base_channel, channel, author, target);
	return (1);
}
