#include "commands.hpp"
#include "IRCErrors.hpp"

static const size_t mode_count = 4;
static const char mode_name[mode_count] = {'O', 'o', 'i', 'k'};
void (*const manageFlags[mode_count])(Message&, Dependencies&, bool, size_t) = {flag_creator, flag_operator, flag_invite, flag_key};

static bool	forbiddenChannelPrefix(char &chan_prefix)
{
	const std::string	allowed_char = "#&!";

	for (std::string::const_iterator it = allowed_char.begin(); it != allowed_char.end(); ++it)
	{
		if (*it == chan_prefix)
			return (false);
	}
	return (true);
}

void	flag_creator(Message &message, Dependencies &deps, bool add_flag, size_t i)
{
	(void)message;
	(void)deps;
	(void)flag;
	(void)i;
	return ; // ONLY GIVEN TO CHANNEL CREATOR, STILL NOT SURE HOW IT SHOULD BE HANDLED IN MODE COMMAND
}

void	flag_operator(Message &message, Dependencies &deps, bool add_flag, size_t i)
{
	// NEED TO ACCESS THE USER flags, SO deps.channels._channels.users.peer.flags ?
	std::map::iterator	it = deps.channels._channels.find(message.argument[0]);
}

void	flag_invite(Message &message, Dependencies &deps, bool add_flag, size_t i)
{
	std::map::iterator	it = deps.channels._channels.find(message.argument[0]);
	if (add_flag == true)
		*it._flags |= FLAG_INVITE;
	if (add_flag == false)
		*it._flags &= ~FLAG_INVITE;
}

void	flag_key(Message &message, Dependencies &deps, bool add_flag, size_t i)
{
	std::map::iterator	it = deps.channels._channels.find(message.argument[0]);
	if (add_flag == true)
	{
		*it.setKey(message.arguments[i + 1]);
		*it._flags |= FLAG_KEY;
	}
	if (add_flag == false)
	{
		*it.unsetKey();
		*it._flags &= ~FLAG_KEY;
	}
}

int	command_mode(Message &message, Dependencies &deps)
{
	if (message.argCount < 2)
		throw ERR_NEEDMOREPARAMS(message.command);
	if (forbiddenChannelPrefix(message.arguments[0][0]))
		return (1);
	if (!deps.channels.exist(message.arguments[0]))
		return (1);
	size_t	i = 0;
	size_t	j;
	size_t	k;
	bool	add_flag;
	for (i = 0; i < message.argCount; i += 2)
	{
		j = 1;
		k = 0;
		add_flag = false;
		if (message.arguments[i][0] != '+' && message.arguments[i][0] != '-')
			continue;
		if (message.arguments[i][0] == '+')
			add_flag = true;
		if (message.arguments[i][j] == mode_name[k])
			manageFlags[k](message, deps, add_flag, i);
		if (j == mode_count)
			throw ERR_UNKNOWNMODE(message.arguments[2][j], message.arguments[0]);
	}
	return (1);	
}
