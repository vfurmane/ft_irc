#include "commands.hpp"

void	command_privmsg_channel(Dependencies &deps, Peer &peer, const _base_channel &base_channel, const std::string text_to_send)
{
	if (!deps.channels.has(base_channel))
	{
		peer.sendMessage(ERR_NOSUCHCHANNEL(base_channel.getName()));
#ifndef NDEBUG
		std::cerr << "The channel " << base_channel.stringify() << " was not found..." << std::endl;
#endif
		return ;
	}
	const Channel	&target = deps.channels.get(base_channel);
	target.sendMessage(PrivmsgMessage(peer, base_channel.stringify(), text_to_send, false));
}
