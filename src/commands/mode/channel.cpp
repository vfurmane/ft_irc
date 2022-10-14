#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

static const size_t mode_count = 3;
static const char mode_name[mode_count] = {'o', 'i', 'k'};
void (*const manageFlags[mode_count])(Message&, Dependencies&, bool, size_t, User&, const std::string&) = {flag_operator, flag_invite_only, flag_key};

void	command_mode_channel(Message &message, Dependencies &deps, const std::string &channel_name)
{
	User	&author = deps.channels.get(channel_name).users[message.peer.getUsername()];
	std::string::const_iterator	it;
	size_t	k;
	bool	add_flag;
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
		++it;
		while (it < message.arguments[i].end())
		{
			k = 0;
			while (k < mode_count)
			{
				if (*it == mode_name[k])
				{
					manageFlags[k](message, deps, add_flag, i, author, channel_name);
					break ;
				}
				k++;
			}
			if (k == mode_count)
				throw ERR_UNKNOWNMODE(std::string(1, *it), message.arguments[0]);
			++it;
		}
	}
}
