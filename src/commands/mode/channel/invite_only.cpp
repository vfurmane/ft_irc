#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_invite_only(bool add_flag, User &author, Channel &channel, const std::string &argument)
{
	(void)argument;
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(channel.getName());
	if (add_flag == true)
		channel.setFlag(FLAG_INVITE);
	else
		channel.unsetFlag(FLAG_INVITE);
}
