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
