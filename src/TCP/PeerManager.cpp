#include "TCP/PeerManager.hpp"

PeerManager::PeerManager(void)
{

}

PeerManager::PeerManager(const PeerManager &obj)
{
	this->_peerMap = obj._peerMap;
}

PeerManager &PeerManager::operator=(const PeerManager &rhs)
{
	this->_peerMap = rhs._peerMap;
	return (*this);
}

PeerManager::~PeerManager(void)
{
	
}

void PeerManager::addPeer(Peer peer)
{
	this->_peerMap.insert(std::make_pair(peer.getFd(), peer));
}

void PeerManager::removePeer(Peer peer)
{
	this->_peerMap.erase(peer.getFd());
}
