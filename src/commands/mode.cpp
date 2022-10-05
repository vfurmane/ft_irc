#include "commands.hpp"
#include "IRCErrors.hpp"

static const size_t mode_count = 4;
static const char mode_name[mode_count] = {'O', 'o', 'i', 'k'};
int (*const add_flags[mode_count])(Message&, Dependencies&) = {flag_creator, flag_operator, flag_invite, flag_key};

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
	for (i = 0; i < message.argCount; i += 2)
	{
		j = 1;
		k = 0;
		if (message.arguments[i][0] != '+' && message.arguments[i][0] != '-')
			continue;
		if (message.arguments[i][j] == mode_name[k])
		{
			add_flags[k](message, deps); // CHECK IF IT WORKS IN ALL CASES
		}
		if (j == mode_count)
		{
			throw ERR_UNKNOWNMODE(message.arguments[2][j], deps.channels.); // CREATE A METHOD TO GET CHANNEL NAME
		}
	}
	return (1);	
}
