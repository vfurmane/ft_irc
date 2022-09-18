#ifndef TCP_PEER_HPP
# define TCP_PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <sys/socket.h>
# include <unistd.h>

class TCPPeer
{
	public:
		TCPPeer(const int fd, struct sockaddr &addr);
		TCPPeer(const TCPPeer &obj);
		TCPPeer &operator=(const TCPPeer &rhs);
		~TCPPeer(void);

		int				close(void) const;

		char			*getStrAddr(void) const;
		int				getFd(void) const;

	private:
		int				_fd;
		struct sockaddr	_addr;
};

#endif
