#include "commands.hpp"
#include "IRCMessage.hpp"
#include "IRCPeer.hpp"

ErrorMessage::ErrorMessage(IRCPeer &peer, const std::string &quit_message) : IRCMessage(peer, std::string())
{
	(void)quit_message;
}

NickMessage::NickMessage(IRCPeer &peer, const std::string &new_nick) : IRCMessage(peer, std::string())
{
	this->command = "NICK";
	this->arguments[0] = new_nick;
	this->argCount = 1;
	this->input = updateInputFromFields();
}
