#ifndef TCPSERVER_HPP
# define TCPSERVER_HPP

# define BACKLOG 256
# define MAX_EVENTS 256
# define TIMEOUT 1000

# include <arpa/inet.h>
# include <cstring>
# include <errno.h>
# include <netdb.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/epoll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
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
			Server(const Server &obj);
			~Server(void);
		
			Server		&operator=(const Server &rhs);
	
			void		listen(void);
	
			void		setHandler(e_handler_type type, int (*handler)(epoll_event *));
	
			struct noBindableAddress : public std::exception {
				virtual const char* what() const throw()
				{
					return "no bindable address";
				}
			};
	
			struct sysCallError : public std::exception {
				std::string _str;
				sysCallError(const std::string &syscall, const std::string &str) : _str(syscall + ": " + str) {}
				~sysCallError(void) throw() {}
				virtual const char* what() const throw()
				{
					return this->_str.c_str();
				}
			};
	
		private:
			void		_bindNewSocketToPort(char *port);
			void		_addFdToEpoll(int new_fd) const;
			void		_registerNewPeer(int new_fd, struct sockaddr &addr);
			void		_handleReadyFds(int event_count, struct epoll_event *events);
	
			int			_sockfd;
			int			_epollfd;
			PeerManager	_peers;
			int			(*_handlers[1])(epoll_event *);
	};

};

#endif
