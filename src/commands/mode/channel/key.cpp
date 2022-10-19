#include "commands.hpp"

void	flag_key(bool add_flag, User &author, Channel &channel, const std::string &argument)
{
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(channel.getName());
	if (add_flag == true)
	{
		channel.setKey(argument);
		channel.setFlag(FLAG_KEY);
	}
	else
	{
		channel.unsetKey();
		channel.unsetFlag(FLAG_KEY);
	}
}
