#include "commands.hpp"

int	command_mode(Message &message, Dependencies &deps)
{
	if (message.argCount < 2)
		throw ERR_NEEDMOREPARAMS(message.command);
	if (!_base_channel::isValidName(message.arguments[0]))
		return (1);
	_base_channel base_channel = _base_channel::parse(message.arguments[0]);
	command_mode_channel(message, deps, base_channel);
	return (1);
}
