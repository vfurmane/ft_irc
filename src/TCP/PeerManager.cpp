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

Peer	&PeerManager::operator[](int fd)
{
	return this->get(fd);
}

void PeerManager::addPeer(Peer peer)
{
	this->_peerMap.insert(std::make_pair(peer.getFd(), peer));
}

void PeerManager::removePeer(int fd)
{
	this->_peerMap.erase(fd);
}

Peer	&PeerManager::get(int fd)
{
	return this->_peerMap.at(fd);
}
