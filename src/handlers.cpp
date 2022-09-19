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

struct inputLexer lexer(const std::string &input)
{
	struct inputLexer	lexer;
	bool				trailingArg = false;
	int					i = 0;
	int					j = 0;
	int					argNumber = 0;
	
	if (input[0] == ':')
	{
		i++;
		lexer.prefix = new std::string;
		while (input[i] != ' ')
			i++;
		*lexer.prefix = input.substr(1, i - 1);
		i++;
	}
	else
		lexer.prefix = NULL;
	while (input[i + j] != ' ')
		j++;
	lexer.command = input.substr(i, j);
	i += j + 1;
	while (input[i] != '\r' && input[i] != '\n' && argNumber < 16)
	{
		j = 0;
		if (input[i] == ':' && input[i - 1] == ' ')
		{
			trailingArg = true;
			break ;
		}
		if (input[i] == ' ' && input[i - 1] == ' ')
		{
			lexer.arguments[argNumber] = ' ';
			i++;
			argNumber++;
			continue ;
		}
		while (input[i + j] != ' ' && input[i + j] != '\r')
			j++;
		lexer.arguments[argNumber] = input.substr(i, j);
		i += j + 1;
		argNumber++;
	}
	j = 0;
	if (trailingArg == true && argNumber < 16)
	{
		while (input[i + j] != '\r')
			j++;
		lexer.arguments[argNumber] = input.substr(i, j);
	}
	return (lexer);
}
