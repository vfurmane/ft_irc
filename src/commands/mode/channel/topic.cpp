#include "commands.hpp"

void	flag_topic(bool add_flag, User &author, Channel &channel, const std::string &argument)
{
	(void)argument;
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(channel.stringify());
	if (add_flag == true)
		channel.setFlag(FLAG_TOPIC);
	else
		channel.unsetFlag(FLAG_TOPIC);
}
