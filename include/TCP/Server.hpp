#ifndef TCPSERVER_HPP
# define TCPSERVER_HPP

# define BACKLOG 256
# define MAX_EVENTS 256
# define TIMEOUT 1000

# include <arpa/inet.h>
# include <cstring>
# include <errno.h>
# include <iostream>
# include <netdb.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/epoll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
# include "exception.hpp"

class PeerManager;
# include "TCP/PeerManager.hpp"

# ifndef NDEBUG
#  include <iostream>
# endif

class PeerManager;
# include "TCP/PeerManager.hpp"

typedef enum handler_type
{
	HDL_MESSAGE
} e_handler_type;

namespace TCP {

	class Server
	{
		public:
			Server(char *port);
			~Server(void);
	
			void		listen(void);
	
			void		setHandler(e_handler_type type, int (*handler)(epoll_event *));
			int			getEpollFd(void) const;
			int			getSocketFd(void) const;
	
			struct noBindableAddress : public std::exception {
				virtual const char* what() const throw()
				{
					return "no bindable address";
				}
			};
	
			struct handlersNotSet : public std::exception {
				virtual const char* what() const throw()
				{
					return "handlers have not been set";
				}
			};
	
		private:
			void		_bindNewSocketToPort(char *port);
			void		_addFdToEpoll(int new_fd) const;
			void		_handleReadyFds(int event_count, struct epoll_event *events);
	
			int			_sockfd;
			int			_epollfd;
			PeerManager	_peers;
			static const size_t _handlers_nb = 1;
			int			(*_handlers[_handlers_nb])(epoll_event *);
	};

};

#endif
