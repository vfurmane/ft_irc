#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <exception>

# include "TCPPeer.hpp"
# include "TCPServer.hpp"
# include "handlers.hpp"

# include "IRCPeerManager.hpp"

class IRCServer: public TCPServer
{
	public:
		IRCServer(char *port);
		~IRCServer(void);

		virtual void		setHandler(e_handler_type type, int (*handler)(TCPPeer *, epoll_event *));
		
		struct cannotSetHandler: public std::exception {
			virtual const char* what() const throw()
			{
				return "cannot set commands handler inside IRCServer";
			};
		};	

	private:
		IRCPeerManager	_peers;
};

#endif
