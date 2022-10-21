#include "IRCReplies.hpp"

RPL_WELCOME::RPL_WELCOME(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	Configuration	&config = peer.server.config;
	this->command = "001";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "Welcome to the " + config.getNetworkName() + " Network " + peer.generatePrefix();
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_YOURHOST::RPL_YOURHOST(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	Configuration	&config = peer.server.config;
	this->command = "002";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "Your host is " + config.getServerName() + ", running version " + config.getServerVersion();
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_CREATED::RPL_CREATED(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	Configuration	&config = peer.server.config;
	this->command = "003";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "This server was created " + config.getServerCreationDate();
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_MYINFO::RPL_MYINFO(Peer &peer, bool include_prefix) : Message(peer, std::string())
{
	Configuration	&config = peer.server.config;
	this->command = "004";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = "" + config.getServerName() + " " + config.getServerVersion() + " " + config.getUserModes() + " " + config.getChannelModes();
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_WHOISUSER::RPL_WHOISUSER(Peer &peer, const Peer &target, bool include_prefix) : Message(peer, std::string())
{
	this->command = "311";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = target.getNickname();
	this->arguments[2] = target.getUsername();
	this->arguments[3] = target.getStrAddr();
	this->arguments[4] = "*";
	this->arguments[5] = target.getRealname();
	this->argCount = 6;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_WHOISSERVER::RPL_WHOISSERVER(Peer &peer, const Peer &target, Configuration &config, bool include_prefix) : Message(peer, std::string())
{
	this->command = "312";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = target.getNickname();
	this->arguments[2] = config.getServerName();
	this->arguments[3] = ":" + config.getNetworkName();
	this->argCount = 4;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_ENDOFWHOIS::RPL_ENDOFWHOIS(Peer &peer, const Peer &target, bool include_prefix) : Message(peer, std::string())
{
	this->command = "318";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = target.getNickname();
	this->arguments[2] = ":End of WHOIS list";
	this->argCount = 3;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_WHOISCHANNELS::RPL_WHOISCHANNELS(Peer &peer, const Peer &target, const std::string &list_of_channels, bool include_prefix) : Message(peer, std::string())
{
	this->command = "319";
	this->arguments[0] = peer.getNickname();
	this->arguments[1] = target.getNickname();
	this->arguments[2] = list_of_channels;
	this->argCount = 3;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

RPL_INVITING::RPL_INVITING(Peer &peer, const std::string &author_nick, const std::string &target_nick, Channel &channel, bool include_prefix) : Message(peer, std::string())
{
	this->command = "341";
	this->arguments[0] = author_nick;
	this->arguments[1] = target_nick;
	this->arguments[2] = channel.stringify();
	this->argCount = 3;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}
