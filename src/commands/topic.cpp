#include "commands.hpp"

int	command_topic(Message &message, Dependencies &deps)
{
	if (message.argCount < 1)
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), message.command);

	if (!_base_channel::isValidName(message.arguments[0]))
		throw ERR_NOSUCHCHANNEL(message.peer.getNickname(), message.arguments[0]);
	_base_channel base_channel = _base_channel::parse(message.arguments[0]);
	if (!deps.channels.has(base_channel.getName()))
		throw ERR_NOSUCHCHANNEL(message.peer.getNickname(), message.arguments[0]);

	Channel	&channel = deps.channels.get(base_channel);
	if (message.argCount == 1)
	{
		if (channel.getTopic().empty())
			message.peer.sendMessage(RPL_NOTOPIC(message.peer, channel));
		else
			message.peer.sendMessage(RPL_TOPIC(message.peer, channel));
	}
	else
	{
		if (!channel.users.hasByNickname(message.peer.getNickname()))
			throw ERR_NOTONCHANNEL(message.peer.getNickname(), channel.stringify());
		User	&user = channel.users.getByNickname(message.peer.getNickname());
		if (channel.hasFlag(FLAG_TOPIC) && user.getStatus() == CHANNEL_USER)
			throw ERR_CHANOPRIVSNEEDED(message.peer.getNickname(), channel.stringify());
		channel.setTopic(message.arguments[1]);
		channel.sendMessage(TopicMessage(message.peer, channel), true);
	}
	return 1;
}
