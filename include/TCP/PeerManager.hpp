#ifndef PEERMANAGER_HPP
# define PEERMANAGER_HPP

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
		void	removePeer(Peer peer);

	private:
		std::map<int, uint16_t> _peerMap;
};

#endif
