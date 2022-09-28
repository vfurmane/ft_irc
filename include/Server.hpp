#ifndef SERVER_HPP
# define SERVER_HPP

# define BACKLOG 256
# define MAX_EVENTS 256
# define TIMEOUT 1000

# define MAX_READ 63

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
# include "Message.hpp"
# include "Peer.hpp"
# include "PeerManager.hpp"

# ifndef NDEBUG
#  include <iostream>
# endif

class Server
{
	public:
		Server(char *port);
		~Server(void);

		void		listen(void);

		int			getEpollFd(void) const; // DELETE
		int			getSocketFd(void) const; // DELETE

		struct noBindableAddress : public std::exception {
			virtual const char* what() const throw()
			{
				return "no bindable address";
			}
		};

	private:
		void		_bindNewSocketToPort(char *port);
		void		_addFdToEpoll(int new_fd) const;
		int			_handle_message(epoll_event &event);
		void		_handleReadyFds(int event_count, struct epoll_event *events);

		PeerManager	_peers;
		int			_sockfd;
		int			_epollfd;
};

#endif