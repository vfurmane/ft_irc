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

int	IRCPeerManager::acceptConnection(void)
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

void	IRCPeerManager::closeConnection(int fd)
{
#ifndef NDEBUG
	std::cerr << "Closing connection on fd no " << fd << "..." << std::endl;
	std::cerr << "IP address -> " << this->get(fd).getStrAddr() << std::endl;
#endif
	if (this->_peers.at(fd).close() == -1)
		throw sysCallError("close", strerror(errno));
	this->remove(fd);
}

IRCPeerManager::const_iterator	IRCPeerManager::begin() const
{
	return this->_peers.begin();
}

IRCPeerManager::const_iterator	IRCPeerManager::end() const
{
	return this->_peers.end();
}
