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
	if (message.argCount < 1 || message.arguments[0].empty())
		throw ERR_NONICKNAMEGIVEN();
	if (deps.peers.containsNickname(message.arguments[0]))
		throw ERR_NICKNAMEINUSE(message.arguments[0]);
	if (!isValidNickname(message.arguments[0]))
		throw ERR_ERRONEUSNICKNAME(message.arguments[0]);
	message.peer.setNickname(message.arguments[0]);
	for (PeerManager::const_iterator it = deps.peers.begin(); it != deps.peers.end(); ++it)
		it->second.sendMessage(NickMessage(message.peer, message.arguments[0]));
	return 1;
}
