#include "IRCReplies.hpp"

RPL_WELCOME::RPL_WELCOME(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	this->command = "001";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "Welcome to the " NETWORK_NAME " Network " + peer.generatePrefix();
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_YOURHOST::RPL_YOURHOST(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	this->command = "002";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "Your host is " SERVER_NAME ", running version " SERVER_VERSION;
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_CREATED::RPL_CREATED(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	this->command = "003";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "This server was created " SERVER_CREATION_DATE;
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_MYINFO::RPL_MYINFO(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	this->command = "004";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "" SERVER_NAME " " SERVER_VERSION " " AVAILABLE_USER_MODES " " AVAILABLE_CHANNEL_MODES;
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}
