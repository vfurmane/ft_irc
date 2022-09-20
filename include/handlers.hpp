#ifndef HANDLERS_HPP
# define HANDLERS_HPP

# include <string>
# include <sys/epoll.h>
# include <sys/socket.h>

# ifndef NDEBUG
#  include <iostream>
# endif

# define MAX_READ 63

int	handleTCPMessage(epoll_event *event);
int	handleIRCMessage(epoll_event *event);
struct inputLexer	lexer(const std::string &input);

typedef struct inputLexer
{
	std::string		*prefix;
	std::string		command;
	std::string		arguments[15];
}	inputLexer;

typedef struct parsedPrefix // UNUSED
{
	std::string	serverName;
	std::string	nickname;
	std::string	user;
	std::string	host;
}	parsedPrefix;

#endif
