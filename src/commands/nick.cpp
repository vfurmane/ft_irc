#include "commands.hpp"

static bool isLetter(char c)
{
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
		return false;
	return true;
}

static bool isDigit(char c)
{
	if (c < '0' || c > '9')
		return false;
	return true;
}

static bool isSpecialCharacter(char c)
{
	static const std::string special_chars = "[]\\`_^{|}";

	return special_chars.find(c) != std::string::npos;
}

static bool	isValidNickname(const std::string &nick)
{
	if (nick.empty() || nick.length() > 9)
		return false;
	if (!isLetter(nick[0]) && !isSpecialCharacter(nick[0]))
		return false;
	for (std::string::const_iterator it = nick.begin(); it < nick.end(); ++it)
	{
		if (!isLetter(*it) && !isDigit(*it) && !isSpecialCharacter(*it) && *it != '-')
			return false;
	}
	return true;
}

int		command_nick(Message &message, Dependencies &deps)
{
	const std::string	&nick = message.arguments[0];

	if (message.argCount < 1 || nick.empty())
		throw ERR_NONICKNAMEGIVEN();
	if (deps.peers.containsNickname(nick))
		throw ERR_NICKNAMEINUSE(nick);
	if (!isValidNickname(nick))
		throw ERR_ERRONEUSNICKNAME(nick);
	message.peer.setNickname(nick);
	for (PeerManager::const_iterator it = deps.peers.begin(); it != deps.peers.end(); ++it)
		it->second.sendMessage(NickMessage(message.peer, nick));
	return 1;
}
