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

JoinMessage::JoinMessage(Peer &peer, const _base_channel &channel, bool include_prefix) : Message(peer, std::string())
{
	this->command = "JOIN";
	this->arguments[0] = channel.stringify();
	this->argCount = 1;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

ModeMessage::ModeMessage(Peer &peer, const _base_channel &channel, const std::string flag, const std::string argument, bool include_prefix) : Message(peer, std::string())
{
	this->command = "MODE";
	this->arguments[0] = channel.stringify();
	this->arguments[1] = flag;
	this->arguments[2] = argument;
	this->argCount = 3;
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

PartMessage::PartMessage(Peer &peer, const _base_channel &channel, const std::string &part_message, bool include_prefix): Message(peer, std::string())
{
	this->command = "PART";
	this->arguments[0] = channel.stringify();
	this->arguments[1] = part_message;
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

PongMessage::PongMessage(Peer &peer, const std::string &server_name, bool include_prefix) : Message(peer, std::string())
{
	this->command = "PONG";
	this->arguments[0] = server_name;
	this->argCount = 1;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

PrivmsgMessage::PrivmsgMessage(Peer &peer, const std::string &target, const std::string &text_to_send, bool include_prefix) : Message(peer, std::string())
{
	this->command = "PRIVMSG";
	this->arguments[0] = target;
	this->arguments[1] = text_to_send;
	this->argCount = 2;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

QuitMessage::QuitMessage(Peer &peer, const std::string &quit_message, bool include_prefix) : Message(peer, std::string())
{
	this->command = "QUIT";
	this->arguments[0] = "Quit: " + quit_message;
	this->argCount = 1;
	if (include_prefix)
		this->prefix = this->updatePrefixFromPeer();
	this->input = this->updateInputFromFields();
}

std::vector<std::string>	parseList(const std::string &list)
{
	if (list.empty())
		throw std::out_of_range("::parseList");

	std::string::const_iterator	it = list.begin();
	std::string::const_iterator	ite = list.end();
	std::vector<std::string>	ret;

	while (it != ite)
	{
		if (it != list.begin())
			it++;
		std::string::size_type	pos = list.find(",", it - list.begin());
		if (pos == std::string::npos)
			pos = list.size();
		ret.push_back(list.substr(it - list.begin(), pos - (it - list.begin())));
		it += pos - (it - list.begin());
	}
	return ret;
}
