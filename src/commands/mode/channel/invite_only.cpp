#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_invite(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name)
{
	(void)i;
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	Channel	&it = deps.channels.get(channel_name);
	if (add_flag == true)
		it.setFlag(FLAG_INVITE);
	if (add_flag == false)
		it.unsetFlag(FLAG_INVITE);
}
