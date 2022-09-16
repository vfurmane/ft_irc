#ifndef TCP_PEER_HPP
# define TCP_PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <sys/socket.h>
# include <unistd.h>

class Peer
{
	public:
		Peer(const int fd, struct sockaddr &addr);
		Peer(const Peer &obj);
		Peer &operator=(const Peer &rhs);
		~Peer(void);

		char			*getStrAddr(void) const;

		int				getFd(void) const;

	private:
		int				_fd;
		struct sockaddr	_addr;
};

#endif
