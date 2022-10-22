#include "Message.hpp"

static const size_t commands_count = 17;
const std::string Message::commands_name[commands_count] = {"CAP", "INVITE", "JOIN", "KICK", "LIST", "MODE", "NAMES", "NICK", "NOTICE", "PART", "PASS", "PING", "PRIVMSG", "QUIT", "TOPIC", "USER", "WHOIS"};
int (*const Message::commands[commands_count])(Message&, Dependencies&) = {command_cap, command_invite, command_join, command_kick, command_list, command_mode, command_names, command_nick, command_notice, command_part, command_pass, command_ping, command_privmsg, command_quit, command_topic, command_user, command_whois};

Message::Message(Peer &peer, const std::string &input): peer(peer), input(input), prefix(NULL), command(), arguments(), argCount(0)
{
}

Message::Message(const Message &obj): peer(obj.peer), input(obj.input), prefix(NULL), command(), arguments(), argCount(0)
{
	(*this) = obj;
}

Message &Message::operator=(const Message &rhs)
{
	this->input = rhs.input;
	this->prefix = rhs.prefix;
	this->command = rhs.command;
	for (int i = 0; i < 15; i++)
		this->arguments[i] = rhs.arguments[i];
	this->argCount = rhs.argCount;
	return (*this);
}

Message::~Message()
{
	delete this->prefix;
}

static void	parseArguments(Message &message, std::string::const_iterator &it)
{
	int		j;
	
	while (it != message.input.end() && *it != '\r' && *it != '\n' && message.argCount < 15)
	{
		j = 0;
		if (*it == ':')
		{
			it++;
			while (it != message.input.end() && it[j] != '\r')
				j++;
			message.arguments[message.argCount] = message.input.substr(it - message.input.begin(), j);
		}
		while (it != message.input.end() && it[j] != ' ' && it[j] != '\r')
			j++;
		message.arguments[message.argCount] = message.input.substr(it - message.input.begin(), j);
		it += j + 1;
		message.argCount++;
	}
}

void	Message::parse()
{
	std::string::const_iterator	it = this->input.begin();
	int							j = 0;
	
	if (this->input[0] == ':')
	{
		it++;
		this->prefix = new std::string;
		while (it != this->input.end() && *it != ' ' && *it != '\r')
			it++;
		*this->prefix = this->input.substr(1, it - this->input.begin() - 1);
		it++;
	}
	while (it != this->input.end() && it[j] != ' ' && it[j] != '\r' && it[j] != '\n')
		j++;
	this->command = this->input.substr(it - this->input.begin(), j);
	it += j + 1;
	parseArguments(*this, it);
}

int	Message::execute(Dependencies &deps)
{
	size_t	i;

	for (i = 0; i < commands_count; i++) {
		if (commands_name[i] == this->command) {
#ifndef NDEBUG
			std::cerr << "Found command " << this->command << std::endl;
#endif
			return commands[i](*this, deps);
		}
	}
	if (i == commands_count)
	{
		throw ERR_UNKNOWNCOMMAND(this->peer.getNickname(), this->command);
	}
	return 1;
}

const std::string	&Message::updateInputFromFields(void)
{
	this->input.clear();
	if (this->prefix != NULL)
		this->input += ":" + *this->prefix + " ";
	this->input += this->command;
	for (size_t i = 0; i < this->argCount; i++)
	{
		this->input += " ";
		if (this->arguments[i].find(" ") != std::string::npos)
			this->input += ":";
		this->input += this->arguments[i];
	}
	return this->input;
}

std::string	*Message::updatePrefixFromPeer(void)
{
	if (this->prefix == NULL)
		this->prefix = new std::string;
	*this->prefix = this->peer.generatePrefix();
	return this->prefix;
}
