#ifndef TCP_PEER_HPP
# define TCP_PEER_HPP
# include <stdint.h>
# include <unistd.h>

class Peer
{
	public:
		Peer(const int fd, const uint16_t address);
		Peer(const Peer &obj);
		Peer &operator=(const Peer &rhs);
		~Peer(void);

		int				getFd(void) const;
		uint16_t	getAddress(void) const;

	private:
		int				_fd;
		uint16_t	_address;
};

#endif
