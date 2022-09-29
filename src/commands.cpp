#include "commands.hpp"
#include "Message.hpp"
#include "Peer.hpp"

ErrorMessage::ErrorMessage(Peer &peer, const std::string &message) : Message(peer, std::string())
{
	this->command = "ERROR";
	this->arguments[0] = "Closing link: (" + peer.getUsername() + "@" + peer.getStrAddr() + ") " + message;
	this->argCount = 1;
	this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

NickMessage::NickMessage(Peer &peer, const std::string &new_nick) : Message(peer, std::string())
{
	this->command = "NICK";
	this->arguments[0] = new_nick;
	this->argCount = 1;
	this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}
