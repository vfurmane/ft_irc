#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_operator(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name);
void	flag_invite(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name);
void	flag_key(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name);

static const size_t mode_count = 3;
static const char mode_name[mode_count] = {'o', 'i', 'k'};
void (*const manageFlags[mode_count])(Message&, Dependencies&, bool, size_t, User&, std::string&) = {flag_operator, flag_invite, flag_key};

void	flag_operator(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name)
{
	if (author.flags == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	if (!deps.channels.get(channel_name).users.has(message.arguments[i + 1]))
		return ;
	User	&target = deps.channels.get(channel_name).users[message.arguments[i + 1]];
	if (add_flag == true && target.flags != CHANNEL_CREATOR)
		target.flags = CHANNEL_OPERATOR;
	if (add_flag == false && author.flags == CHANNEL_CREATOR && target.flags != CHANNEL_CREATOR)
		target.flags = CHANNEL_USER;
}

void	flag_invite(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name)
{
	(void)i;
	if (author.flags == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	Channel	&it = deps.channels.get(channel_name);
	if (add_flag == true)
		it.setFlag(FLAG_INVITE);
	if (add_flag == false)
		it.unsetFlag(FLAG_INVITE);
}

void	flag_key(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name)
{
	if (author.flags == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	Channel	&it = deps.channels.get(channel_name);
	if (add_flag == true)
	{
		it.setKey(message.arguments[i + 1]);
		it.setFlag(FLAG_KEY);
	}
	if (add_flag == false)
	{
		it.unsetKey();
		it.unsetFlag(FLAG_KEY);
	}
}

int	command_mode(Message &message, Dependencies &deps)
{
	if (message.argCount < 2)
		throw ERR_NEEDMOREPARAMS(message.command);
	std::string channel_name;
	try
	{
		channel_name = _base_channel::parse(message.arguments[0]).getName();
	} 
	catch (std::exception &e)
	{
		return (1);
	}
	if (!deps.channels.has(channel_name))
		return (1);
	if (!deps.channels.get(channel_name).users.has(message.peer.getUsername()))
		return (1);
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
	return (1);	
}
