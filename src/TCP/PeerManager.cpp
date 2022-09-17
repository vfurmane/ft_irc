#include "TCP/PeerManager.hpp"
#include <cstdio> // DELETE

PeerManager::PeerManager(TCP::Server &server) : _server(server), _peers()
{
}

PeerManager::PeerManager(const PeerManager &obj) : _server(obj._server), _peers()
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

void PeerManager::add(int fd, struct sockaddr &addr)
{
	this->_peers.insert(std::make_pair(fd, Peer(fd, addr)));
#ifndef NDEBUG
	std::cerr << "New peer has been added!" << std::endl;
#endif
}

// TODO should only remove, should add a closeConnection() method
void PeerManager::remove(int fd)
{
	std::map<int, Peer>::iterator peer_it = this->_peers.find(fd);
#ifndef NDEBUG
	std::cerr << "Closing connection on fd no " << fd << "..." << std::endl;
	std::cerr << "IP address -> " << this->get(fd).getStrAddr() << std::endl;
#endif
	peer_it->second.close();
	this->_peers.erase(peer_it);
}

Peer	&PeerManager::get(int fd)
{
	return this->_peers.at(fd);
}

int	PeerManager::acceptConnection(void)
{
	struct sockaddr their_addr;
	socklen_t sin_size = sizeof their_addr;
	
	int new_fd;
	if ((new_fd = accept(this->_server.getSocketFd(), &their_addr, &sin_size)) == -1)
	{
		close(this->_server.getEpollFd());
		close(this->_server.getSocketFd());
		throw TCP::Server::sysCallError("accept", strerror(errno));
	}
#ifndef NDEBUG
	std::cerr << "Accepted connection on fd no " << new_fd << "!" << std::endl;
	std::cerr << "IP address -> " << inet_ntoa(((struct sockaddr_in *)(&their_addr))->sin_addr) << std::endl;
#endif
	this->add(new_fd, their_addr);
	return new_fd;
}

void	PeerManager::closeConnection(int fd)
{
#ifndef NDEBUG
	std::cerr << "Closing connection on fd no " << fd << "..." << std::endl;
	std::cerr << "IP address -> " << this->get(fd).getStrAddr() << std::endl;
#endif
	this->_peers.at(fd).close();
	this->remove(fd);
}
