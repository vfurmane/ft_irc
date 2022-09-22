#include "IRCMessage.hpp"

static const size_t commands_count = 0;
const std::string IRCMessage::commands_name[commands_count] = {};
void (*const IRCMessage::commands[commands_count])(void) = {};

IRCMessage::IRCMessage(IRCPeer &peer, const std::string &input): peer(peer), _input(input), _prefix(NULL), _command(), _arguments(), _argCount(0)
{
}

IRCMessage::IRCMessage(const IRCMessage &obj)
{
	(*this) = obj;
}

IRCMessage &IRCMessage::operator=(const IRCMessage &rhs)
{
	this->_input = rhs._input;
	this->_prefix = rhs._prefix;
	this->_command = rhs._command;
	for (int i = 0; i < 15; i++)
		this->_arguments[i] = rhs._arguments[i];
	this->_argCount = rhs._argCount;
	return (*this);
}

IRCMessage::~IRCMessage()
{
	delete this->_prefix;
}

void	IRCMessage::_parseArguments(std::string::const_iterator &it)
{
	int		j;
	
	while (it != this->_input.end() && *it != '\r' && *it != '\n' && this->_argCount < 15)
	{
		j = 0;
		if (*it == ':')
		{
			it++;
			while (it != this->_input.end() && it[j] != '\r')
				j++;
			this->_arguments[_argCount] = this->_input.substr(it - this->_input.begin(), j);
		}
		while (it != this->_input.end() && it[j] != ' ' && it[j] != '\r')
			j++;
		this->_arguments[_argCount] = this->_input.substr(it - this->_input.begin(), j);
		it += j + 1;
		_argCount++;
	}
}

void	IRCMessage::parse()
{
	std::string::const_iterator	it = this->_input.begin();
	int							j = 0;
	
	if (this->_input[0] == ':')
	{
		it++;
		this->_prefix = new std::string;
		while (it != this->_input.end() && *it != ' ' && *it != '\r')
			it++;
		*this->_prefix = this->_input.substr(1, it - this->_input.begin() - 1);
		it++;
	}
	while (it != this->_input.end() && it[j] != ' ' && it[j] != '\r' && it[j] != '\n')
		j++;
	this->_command = this->_input.substr(it - this->_input.begin(), j);
	it += j + 1;
	_parseArguments(it);
}

void	IRCMessage::execute()
{
	for (size_t i = 0; i < commands_count; i++) {
		if (commands_name[i] == this->_command) {
			commands[i]();
		}
	}
}

size_t	IRCMessage::getArgsCount(void) const
{
	return this->_argCount;
}

const std::string	*IRCMessage::getArguments(void) const
{
	return this->_arguments;
}

const std::string	&IRCMessage::getInput(void) const
{
	return this->_input;
}

const std::string	&IRCMessage::_updateInputFromFields(void)
{
	this->_input.clear();
	if (this->_prefix != NULL)
		this->_input += ":" + *this->_prefix + " ";
	this->_input += this->_command;
	for (size_t i = 0; i < _argCount; i++)
	{
		this->_input += " ";
		if (this->_arguments[i].find(" ") != std::string::npos)
			this->_input += ":";
		this->_input += this->_arguments[i];
	}
	return this->_input;
}
