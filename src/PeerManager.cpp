#include "PeerManager.hpp"
#include <map>

PeerManager::PeerManager(Server &server) : _server(server), _peers()
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

PeerManager::const_iterator	PeerManager::begin(void) const
{
	return this->_peers.begin();
}

PeerManager::const_iterator	PeerManager::end(void) const
{
	return this->_peers.end();
}

void PeerManager::add(int fd, struct sockaddr &addr)
{
	std::pair<std::map<int, Peer>::iterator, bool>	ret = this->_peers.insert(std::make_pair(fd, Peer(fd, addr)));
#ifndef NDEBUG
	if (ret.second)
		std::cerr << "New peer has been added!" << std::endl;
	else
		std::cerr << "No peer has been added!" << std::endl;
#endif
}

void PeerManager::remove(int fd)
{
	int ret = this->_peers.erase(fd);
#ifndef NDEBUG
	std::cerr << "Deleted " << ret << " element" << std::endl;
#endif
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
		throw sysCallError("accept", strerror(errno));
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
	if (this->_peers.at(fd).close() == -1)
		throw sysCallError("close", strerror(errno));
	this->remove(fd);
}
