#include "commands.hpp"

static void	add_invitation(Message &message, Channel &target_channel)
{
	if (target_channel.users.hasByNickname(message.arguments[0]))
		throw ERR_USERONCHANNEL(message.arguments[0], message.arguments[1]);
	else
	{
		target_channel.addInvitation(message.arguments[0]);
		message.peer.sendMessage(RPL_INVITING(message.peer, message.arguments[1], message.arguments[0], false));
	}
}

int	command_invite(Message &message, Dependencies &deps)
{
	if (message.argCount < 2)
		throw ERR_NEEDMOREPARAMS("INVITE");

	if (!_base_channel::isValidName(message.arguments[1]))
		return 1;
	_base_channel base_channel = _base_channel::parse(message.arguments[1]);
	if (deps.channels.has(base_channel))
	{
		if (!deps.peers.hasByNickname(message.arguments[0]))
			throw ERR_NOSUCHNICK(message.arguments[0]);

		Channel target_channel(deps.channels.get(base_channel));

		if (!target_channel.users.hasByNickname(message.peer.getNickname()))
			throw ERR_NOTONCHANNEL(message.arguments[1]);
		else
		{
			if ((target_channel.getFlags() & FLAG_INVITE) == FLAG_INVITE)
			{
				if (target_channel.users.getByNickname(message.peer.getNickname()).getStatus() > 0)
					add_invitation(message, target_channel);
				else
					throw ERR_CHANOPRIVSNEEDED(message.arguments[1]);
			}
			else
				add_invitation(message, target_channel);
		}
	}
	return 1;
}
