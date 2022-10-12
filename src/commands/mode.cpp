#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_operator(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author);
void	flag_invite(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author);
void	flag_key(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author);

static const size_t mode_count = 3;
static const char mode_name[mode_count] = {'o', 'i', 'k'};
void (*const manageFlags[mode_count])(Message&, Dependencies&, bool, size_t, User&) = {flag_operator, flag_invite, flag_key};

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

void	flag_operator(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author)
{
	if (author.flags == channel_user)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	if (!deps.channels.get(message.arguments[0]).users.has(message.arguments[i + 1]))
		return ;
	User	target = deps.channels.get(message.arguments[0]).users[message.arguments[i + 1]];
	if (add_flag == true && target.flags != channel_creator)
		target.flags = channel_operator;
	if (add_flag == false && author.flags == channel_creator && target.flags != channel_creator)
		target.flags = channel_user;
}

void	flag_invite(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author)
{
	(void)i;
	if (author.flags == channel_user)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	Channel	&it = deps.channels.get(message.arguments[0]);
	if (add_flag == true)
		it.getFlags() |= FLAG_INVITE;
	if (add_flag == false)
		it.getFlags() &= ~FLAG_INVITE;
}

void	flag_key(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author)
{
	if (author.flags == channel_user)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	Channel	&it = deps.channels.get(message.arguments[0]);
	if (add_flag == true)
	{
		it.setKey(message.arguments[i + 1]);
		it.getFlags() |= FLAG_KEY;
	}
	if (add_flag == false)
	{
		it.unsetKey();
		it.getFlags() &= ~FLAG_KEY;
	}
}

int	command_mode(Message &message, Dependencies &deps)
{
	if (message.argCount < 2)
		throw ERR_NEEDMOREPARAMS(message.command);
	if (forbiddenChannelPrefix(message.arguments[0][0]))
		return (1);
	if (!deps.channels.has(message.arguments[0]))
		return (1);
	User	&author = deps.channels.get(message.arguments[0]).users[message.peer.getUsername()];
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
			manageFlags[k](message, deps, add_flag, i, author);
		if (j == mode_count)
			throw ERR_UNKNOWNMODE(std::string(1, message.arguments[2][j]), message.arguments[0]);
	}
	return (1);	
}
