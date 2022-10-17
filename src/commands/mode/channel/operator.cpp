#include "Channel.hpp"
#include "User.hpp"
#include "commands.hpp"
#include "IRCErrors.hpp"

void	flag_operator(bool add_flag, User &author, Channel &channel, const std::string &argument)
{
	if (author.getStatus() == CHANNEL_USER)
		throw ERR_CHANOPRIVSNEEDED(channel.getName());
	if (!channel.users.hasByNickname(argument))
		return ;
	User	&target = channel.users.getByNickname(argument);
	if (add_flag == true && target.getStatus() != CHANNEL_CREATOR)
		target.setStatus(CHANNEL_OPERATOR);
	if (add_flag == false && author.getStatus() == CHANNEL_CREATOR && target.getStatus() != CHANNEL_CREATOR)
		target.setStatus(CHANNEL_USER);
}
