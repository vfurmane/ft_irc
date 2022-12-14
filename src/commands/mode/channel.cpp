#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

static const size_t mode_count = 4;
void (*const manageFlags[mode_count])(bool, User&, Channel&, const std::string&) = {flag_invite_only, flag_key, flag_operator, flag_topic};

void	command_mode_channel(Message &message, Dependencies &deps, const _base_channel &base_channel)
{
	if (!deps.channels.has(base_channel))
		throw ERR_NOSUCHCHANNEL(message.peer.getNickname(), message.arguments[0]);
	Channel	&channel = deps.channels.get(base_channel.getName());
	if (!channel.users.has(message.peer.getFd()))
		throw ERR_NOTONCHANNEL(message.peer.getNickname(), message.arguments[0]);
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
			while (k < deps.config.getChannelModes().length())
			{
				if (*it == deps.config.getChannelModes()[k])
				{
					manageFlags[k](add_flag, author, channel, message.arguments[i + 1]);
					break ;
				}
				k++;
			}
			if (k == mode_count)
				message.peer.sendMessage(ERR_UNKNOWNMODE(message.peer.getNickname(), std::string(1, *it), message.arguments[0]));
			else
				flags += *it;
			++it;
		}
		arguments += message.arguments[i + 1];
	}
	if (flags.length() != 1)
	{
		message.peer.sendMessage(ModeChannelMessage(message.peer, base_channel, flags, arguments, true));
		channel.sendMessage(ModeChannelMessage(message.peer, base_channel, flags, arguments));
	}
}
