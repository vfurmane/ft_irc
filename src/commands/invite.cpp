#include "commands.hpp"

static void	add_invitation(Message &message, Peer &target_peer, Channel &target_channel)
{
	if (target_channel.users.hasByNickname(message.arguments[0]))
		throw ERR_USERONCHANNEL(message.peer.getNickname(), message.arguments[0], message.arguments[1]);
	else
	{
		target_channel.addInvitation(target_peer);
		message.peer.sendMessage(RPL_INVITING(message.peer, message.peer.getNickname(),target_peer.getNickname(), target_channel));
		target_peer.sendMessage(InviteMessage(message.peer, target_peer.getNickname(), target_channel, true));
	}
}

int	command_invite(Message &message, Dependencies &deps)
{
	if (message.argCount < 2 || message.arguments[0].empty() || message.arguments[1].empty())
		throw ERR_NEEDMOREPARAMS(message.peer.getNickname(), "INVITE");

	if (!_base_channel::isValidName(message.arguments[1]))
		return 1;
	_base_channel base_channel = _base_channel::parse(message.arguments[1]);
	if (deps.channels.has(base_channel))
	{
		if (!deps.peers.hasByNickname(message.arguments[0]))
			throw ERR_NOSUCHNICK(message.arguments[0]);

		Channel &target_channel = deps.channels.get(base_channel);
		Peer	&target_peer = deps.peers.getByNickname(message.arguments[0]);

		if (!target_channel.users.hasByNickname(message.peer.getNickname()))
			throw ERR_NOTONCHANNEL(message.peer.getNickname(), message.arguments[1]);
		if ((target_channel.getFlags() & FLAG_INVITE) == FLAG_INVITE &&
				target_channel.users.getByNickname(message.peer.getNickname()).getStatus() == CHANNEL_USER)
			throw ERR_CHANOPRIVSNEEDED(message.peer.getNickname(), message.arguments[1]);
		add_invitation(message, target_peer, target_channel);
	}
	return 1;
}
