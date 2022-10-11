#include "commands.hpp"

ErrorMessage::ErrorMessage(Peer &peer, const std::string &message, bool include_prefix) : Message(peer, std::string())
{
	this->command = "ERROR";
	this->arguments[0] = "Closing link: (" + peer.getUsername() + "@" + peer.getStrAddr() + ") " + "[" + message + "]";
	this->argCount = 1;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

NickMessage::NickMessage(Peer &peer, const std::string &new_nick, bool include_prefix) : Message(peer, std::string())
{
	this->command = "NICK";
	this->arguments[0] = new_nick;
	this->argCount = 1;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}
