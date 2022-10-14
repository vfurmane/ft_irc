#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_operator(Message &message, Dependencies &deps, bool add_flag, size_t i, User &author, std::string &channel_name)
{
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(message.arguments[0]);
	if (!deps.channels.get(channel_name).users.has(message.arguments[i + 1]))
		return ;
	User	&target = deps.channels.get(channel_name).users[message.arguments[i + 1]];
	if (add_flag == true && target.getStatus() != CHANNEL_CREATOR)
		target.setStatus(CHANNEL_OPERATOR);
	if (add_flag == false && author.getStatus() == CHANNEL_CREATOR && target.getStatus() != CHANNEL_CREATOR)
		target.setStatus(CHANNEL_USER);
}
