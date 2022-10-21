#include "commands.hpp"

void	command_notice_nickname(Dependencies &deps, Peer &peer, const std::string &nickname, const std::string text_to_send)
{
	if (!deps.peers.hasByNickname(nickname))
	{
		peer.sendMessage(ERR_NOSUCHNICK(nickname));
#ifndef NDEBUG
		std::cerr << "The nickname " << nickname << " is not in use..." << std::endl;
#endif
		return ;
	}
	const Peer	&target = deps.peers.getByNickname(nickname);
	target.sendMessage(NoticeMessage(peer, nickname, text_to_send, true));
}
