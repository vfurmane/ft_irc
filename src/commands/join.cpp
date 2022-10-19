#include "commands.hpp"

int		command_join(Message &message, Dependencies &deps)
{
	if (message.argCount < 1 || message.arguments[0].empty() || (message.argCount >= 2 && message.arguments[1].empty()))
		throw ERR_NEEDMOREPARAMS("JOIN");

	if (message.arguments[0] == "0")
	{
		message.peer.leaveAllChannels();
		return 1;
	}
	const std::vector<std::string>	channels = parseList(message.arguments[0]);
	const std::vector<std::string>	keys = message.argCount >= 2 ?
		parseList(message.arguments[1]) : std::vector<std::string>();
	
	std::vector<std::string>::const_iterator	chan_it = channels.begin();
	std::vector<std::string>::const_iterator	key_it = keys.begin();
	while (chan_it != channels.end())
	{
		if (_base_channel::isValidName(*chan_it))
		{
			_base_channel base_channel = Channel::parse(*chan_it);
			try
			{
				Channel	&channel = deps.channels[base_channel.getName()];
				if (channel.hasFlag(FLAG_INVITE) && !channel.isInvited(message.peer))
					throw ERR_INVITEONLYCHAN(message.peer.getNickname(), base_channel.stringify());
				else if (key_it != keys.end() && !channel.compareKey(*key_it))
					message.peer.sendMessage(ERR_BADCHANNELKEY(*chan_it));
				else
				{
					channel.add(message.peer);
					channel.users[message.peer.getFd()].setStatus(CHANNEL_USER);
					message.peer.sendMessage(JoinMessage(message.peer, base_channel, true));
					channel.sendMessage(JoinMessage(message.peer, base_channel));
				}
			}
			catch (std::out_of_range &)
			{
				message.peer.createChannel(base_channel);
				message.peer.sendMessage(JoinMessage(message.peer, base_channel, true));
			}
		}
		else
			message.peer.sendMessage(ERR_NOSUCHCHANNEL(*chan_it));
		++chan_it;
		if (key_it != keys.end())
			++key_it;
	}
	return 1;
}
