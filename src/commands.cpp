#include "commands.hpp"
#include "IRCMessage.hpp"
#include "IRCPeer.hpp"

ErrorMessage::ErrorMessage(IRCPeer &peer, const std::string &quit_message) : IRCMessage(peer, std::string())
{
	
}

NickMessage::NickMessage(IRCPeer &peer, const std::string &new_nick) : IRCMessage(peer, std::string())
{
	this->_command = "NICK";
	this->_arguments[0] = new_nick;
	this->_argCount = 1;
	this->_input = _updateInputFromFields();
}
