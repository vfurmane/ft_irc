#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_key(bool add_flag, User &author, Channel &channel, const std::string &argument)
{
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(channel.getName());
	if (add_flag == true)
	{
		channel.setKey(argument);
		channel.setFlag(FLAG_KEY);
	}
	if (add_flag == false)
	{
		channel.unsetKey();
		channel.unsetFlag(FLAG_KEY);
	}
}
