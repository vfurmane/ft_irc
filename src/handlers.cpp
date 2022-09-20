#include "handlers.hpp"

int handleIRCMessage(epoll_event *event)
{
	(void)event;
	return 0;
}

int	handleTCPMessage(epoll_event *event)
{
	int		bytes_read;
	char	buffer[MAX_READ + 1];
	
	bytes_read = recv(event->data.fd, buffer, MAX_READ, 0);
	if (bytes_read <= 0)
		return -1;
	else
	{
		buffer[bytes_read] = '\0';
#ifndef NDEBUG
		std::cerr << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << std::endl;
		std::cerr << buffer;
		if (buffer[bytes_read - 1] != '\n')
			std::cerr << "%" << std::endl;
		std::cerr << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
#endif
	}
	return 0;
}

void	argumentLexer(std::string::iterator &it, struct inputLexer &lexer, const std::string &input)
{
	int		argNumber = 0;
	int		j = 0;
	bool	trailingArg = false;
	
	while (*it != '\r' && *it != '\n' && argNumber < 15)
	{
		j = 0;
		if (*it == ':' && it[1] == ' ')
		{
			trailingArg = true;
			break ;
		}
		while (it[j] != ' ' && it[j] != '\r')
			j++;
		lexer.arguments[argNumber] = input.substr(it - input.begin(), j);
		it += j + 1;
		argNumber++;
	}
	j = 0;
	if (trailingArg == true && argNumber < 15)
	{
		while (it[j] != '\r')
			j++;
		lexer.arguments[argNumber] = input.substr(it - input.begin(), j);
	}
}

struct inputLexer lexer(const std::string &input)
{
	struct inputLexer		lexer;
	std::string::iterator	it;
	int						j = 0;
	
	if (input[0] == ':')
	{
		it++;
		lexer.prefix = new std::string;
		while (*it != ' ')
			it++;
		*lexer.prefix = input.substr(1, it - input.begin() - 1);
		it++;
	}
	else
		lexer.prefix = NULL;
	while (it[j] != ' ')
		j++;
	lexer.command = input.substr(it - input.begin(), j);
	it += j + 1;
	argumentLexer(it, lexer, input);
	return (lexer);
}
