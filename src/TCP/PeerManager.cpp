#include "TCP/PeerManager.hpp"

PeerManager::PeerManager(void) : _peers()
{

}

PeerManager::PeerManager(const PeerManager &obj) : _peers()
{
	this->_peers = obj._peers;
}

PeerManager &PeerManager::operator=(const PeerManager &rhs)
{
	this->_peers = rhs._peers;
	return (*this);
}

PeerManager::~PeerManager(void)
{
	
}

Peer	&PeerManager::operator[](int fd)
{
	return this->get(fd);
}

void PeerManager::add(Peer peer)
{
	this->_peers.insert(std::make_pair(peer.getFd(), peer));
}

void PeerManager::remove(int fd)
{
	this->_peers.erase(fd);
}

Peer	&PeerManager::get(int fd)
{
	return this->_peers.at(fd);
}
