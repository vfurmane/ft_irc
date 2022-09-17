#ifndef TCP_PEERMANAGER_HPP
# define TCP_PEERMANAGER_HPP

# include <map>
# include <algorithm>
# include "Peer.hpp"

class PeerManager
{
	public:
		PeerManager(void);
		PeerManager(const PeerManager &obj);
		PeerManager &operator=(const PeerManager &rhs);
		~PeerManager(void);

		Peer	&operator[](int fd);

		void	add(Peer peer);
		void	remove(int fd);
		Peer	&get(int fd);

	private:
		std::map<int, Peer> _peers;
};

#endif
