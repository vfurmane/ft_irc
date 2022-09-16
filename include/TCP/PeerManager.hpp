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

		void	addPeer(Peer peer);
		void	removePeer(int fd);

	private:
		std::map<int, Peer> _peerMap;
};

#endif
