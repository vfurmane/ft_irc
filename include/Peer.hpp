#ifndef PEER_HPP
# define PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>

class Peer
{
	public:
		Peer(const int fd, struct sockaddr &addr);
		Peer(const Peer &obj);
		Peer &operator=(const Peer &rhs);
		~Peer(void);

		int					close(void) const;
		void				appendMessage(const char *buffer);
		void				clearMessage(void);
		bool				hasCompleteMessage(void) const;
		const std::string	&getMessage(void) const;

		char			*getStrAddr(void) const;
		int				getFd(void) const;

	private:
		int				_fd;
		struct sockaddr	_addr;
		std::string		_message;
};

#endif
