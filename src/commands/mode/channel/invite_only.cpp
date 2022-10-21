#include "commands.hpp"

void	flag_invite_only(bool add_flag, User &author, Channel &channel, const std::string &argument)
{
	(void)argument;
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(author.peer.getNickname(), channel.stringify());
	if (add_flag == true)
		channel.setFlag(FLAG_INVITE);
	else
		channel.unsetFlag(FLAG_INVITE);
}
