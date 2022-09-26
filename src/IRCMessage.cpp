#include "IRCMessage.hpp"

static const size_t commands_count = 0;
const std::string IRCMessage::commands_name[commands_count] = {};
void (*const IRCMessage::commands[commands_count])(void) = {};

IRCMessage::IRCMessage(const std::string &input): input(input), prefix(NULL), command(), arguments(), argCount(0)
{
}

IRCMessage::IRCMessage(const IRCMessage &obj)
{
	(*this) = obj;
}

IRCMessage &IRCMessage::operator=(const IRCMessage &rhs)
{
	this->input = rhs.input;
	this->prefix = rhs.prefix;
	this->command = rhs.command;
	for (int i = 0; i < 15; i++)
		this->arguments[i] = rhs.arguments[i];
	this->argCount = rhs.argCount;
	return (*this);
}

IRCMessage::~IRCMessage()
{
	delete this->prefix;
}

static void	parseArguments(IRCMessage &message, std::string::const_iterator &it)
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

void	IRCMessage::parse()
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

void	IRCMessage::execute()
{
	for (size_t i = 0; i < commands_count; i++) {
		if (commands_name[i] == this->command) {
			commands[i]();
		}
	}
}
