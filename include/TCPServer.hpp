#ifndef TCPSERVER_HPP
# define TCPSERVER_HPP

# define BACKLOG 256
# define MAX_EVENTS 256
# define TIMEOUT 1000
# define MAX_READ 63

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


class TCPServer
{
	public:
		TCPServer(char *port);
		TCPServer(const TCPServer &obj);
		~TCPServer(void);
	
		TCPServer	&operator=(const TCPServer &rhs);

		void		listen(void);

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
		void		_handleReadyFds(int event_count, struct epoll_event *events) const;

		int			_sockfd;
		int			_epollfd;
};

#endif
