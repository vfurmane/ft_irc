#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

static const size_t mode_count = 3;
static const char mode_name[mode_count] = {'o', 'i', 'k'};
void (*const manageFlags[mode_count])(bool, User&, Channel&, const std::string&) = {flag_operator, flag_invite_only, flag_key};

void	command_mode_channel(Message &message, Dependencies &deps, const _base_channel &base_channel)
{
	if (!deps.channels.has(base_channel))
		return;
	Channel	&channel = deps.channels.get(base_channel.getName());
	if (!channel.users.has(message.peer.getFd()))
		return;
	User	&author = channel.users[message.peer.getFd()];
	std::string::const_iterator	it;
	size_t	k;
	bool	add_flag;
	std::string	flags;
	std::string arguments;
	for (size_t i = 1; i < message.argCount; i += 2)
	{
		if (message.arguments[i].size() < 2)
			continue;
		it = message.arguments[i].begin();
		add_flag = false;
		if (*it != '+' && *it != '-')
			continue;
		if (*it == '+')
			add_flag = true;
		flags += *it;
		++it;
		while (it < message.arguments[i].end())
		{
			k = 0;
			while (k < mode_count)
			{
				if (*it == mode_name[k])
				{
					manageFlags[k](add_flag, author, channel, message.arguments[i + 1]);
					break ;
				}
				k++;
			}
			if (k == mode_count)
				throw ERR_UNKNOWNMODE(std::string(1, *it), message.arguments[0]);
			flags += *it;
			++it;
		}
		arguments += message.arguments[i + 1];
	}
	message.peer.sendMessage(ModeMessage(message.peer, base_channel, flags, arguments, true));
	channel.sendMessage(ModeMessage(message.peer, base_channel, flags, arguments));
}
