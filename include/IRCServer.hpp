#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <exception>
# include <iostream>

# include "TCPServer.hpp"

int	handleIRCMessage(epoll_event *event); // REMOVE

class IRCServer: public TCPServer
{
	public:
		IRCServer(char *port);
		~IRCServer(void);

		virtual void		setHandler(e_handler_type type, int (*handler)(epoll_event *));
		
		struct cannotSetHandler: public std::exception {
			virtual const char* what() const throw()
			{
				return "cannot set commands handler inside IRCServer";
			};
		};
	
	private:
		
};

#endif
