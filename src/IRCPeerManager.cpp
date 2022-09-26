#include "IRCPeerManager.hpp"

IRCPeerManager::IRCPeerManager(IRCServer &server) : TCPPeerManager(server), _server(server), _peers()
{
}

IRCPeerManager::IRCPeerManager(const IRCPeerManager &obj) : TCPPeerManager(obj._server), _server(obj._server), _peers()
{
	*this = obj;
}

IRCPeerManager &IRCPeerManager::operator=(const IRCPeerManager &rhs)
{
	this->_peers = rhs._peers;
	return (*this);
}

IRCPeerManager::~IRCPeerManager(void)
{
}

IRCPeer	&IRCPeerManager::operator[](int fd)
{
	return this->get(fd);
}

void IRCPeerManager::add(int fd, struct sockaddr &addr)
{
	this->_peers.insert(std::make_pair(fd, IRCPeer(fd, addr)));
#ifndef NDEBUG
	std::cerr << "New peer has been added!" << std::endl;
#endif
}

void IRCPeerManager::remove(int fd)
{
	this->_peers.erase(fd);
}

IRCPeer	&IRCPeerManager::get(int fd)
{
	return this->_peers.at(fd);
}

IRCPeerManager::const_iterator	IRCPeerManager::begin() const
{
	return this->_peers.begin();
}

IRCPeerManager::const_iterator	IRCPeerManager::end() const
{
	return this->_peers.end();
}
