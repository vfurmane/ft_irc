#ifndef TCP_PEER_HPP
# define TCP_PEER_HPP
# include <stdint.h>
# include <unistd.h>

class Peer
{
	public:
		Peer(const int fd);
		Peer(const Peer &obj);
		Peer &operator=(const Peer &rhs);
		~Peer(void);

		int				getFd(void) const;

	private:
		int				_fd;
};

#endif
