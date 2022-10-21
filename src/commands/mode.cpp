#include "commands.hpp"

int	command_mode(Message &message, Dependencies &deps)
{
	if (message.argCount < 2 || message.arguments[0].empty() || message.arguments[1].empty())
		throw ERR_NEEDMOREPARAMS(message.command);
	if (!_base_channel::isValidName(message.arguments[0]))
	{
		message.peer.sendMessage(ModeUserMessage(message.peer, message.arguments[0], message.arguments[1]));
		if (!deps.peers.hasByNickname(message.arguments[0]))
			throw ERR_NOSUCHNICK(message.arguments[0]);
		if (message.peer.getNickname() != message.arguments[0])
			throw ERR_USERSDONTMATCH();
		return (1);
	}
	_base_channel base_channel = _base_channel::parse(message.arguments[0]);
	command_mode_channel(message, deps, base_channel);
	return (1);
}
