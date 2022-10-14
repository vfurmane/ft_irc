#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_key(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name)
{
	if (author.getStatus() == CHANNEL_USER)
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
