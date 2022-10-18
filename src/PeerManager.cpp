#include "PeerManager.hpp"

PeerManager::PeerManager(Server &server) : Manager(), _server(server)
{
}

PeerManager::PeerManager(const PeerManager &obj) : Manager(obj), _server(obj._server)
{
}

PeerManager &PeerManager::operator=(const PeerManager &rhs)
{
	(void)rhs;
	return (*this);
}

PeerManager::~PeerManager(void)
{
}

Peer	&PeerManager::add(int fd, struct sockaddr &addr)
{
	return Manager::add(fd, Peer(this->_server, fd, addr));
}

static bool	areSameNickname(const std::string &nick1, const std::string &nick2)
{
	if (nick1.length() != nick2.length())
		return false;

	std::string::const_iterator	it1 = nick1.begin();
	std::string::const_iterator	it2 = nick2.begin();
	while (it1 != nick1.end() && it2 != nick2.end())
	{
		if (toIRCLower(*it1) != toIRCLower(*it2))
			return false;
		++it1;
		++it2;
	}
	return true;
}

bool	PeerManager::containsNickname(const std::string &nick) const
{
	for (std::map<int, Peer>::const_iterator it = this->begin(); it != this->end(); ++it)
	{
		if (areSameNickname(it->second.getNickname(), nick))
			return true;
	}
	return false;
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
	if (this->has(new_fd))
	{
#ifndef NDEBUG
		std::cerr << "Critical error: it seems that the fd is already in the manager" << std::endl;
#endif
		close(new_fd);
		throw std::exception();
	}
#ifndef NDEBUG
	Peer	&ret =
#endif
	this->add(new_fd, their_addr);
#ifndef NDEBUG
	std::cerr << "Accepted connection on fd no " << new_fd << "!" << std::endl;
	std::cerr << "Client -> " << ret.getStrAddr() << std::endl;
#endif
	return new_fd;
}

void	PeerManager::closeConnection(Peer &peer)
{
#ifndef NDEBUG
	std::cerr << "Closing connection on fd no " << peer.getFd() << "..." << std::endl;
	std::cerr << "Client -> " << peer.generatePrefix() << std::endl;
#endif
	if (peer.close() == -1)
		throw sysCallError("close", strerror(errno));
	for (ChannelManager::iterator it = this->_server.channels.begin(); it != this->_server.channels.end(); ++it)
	{
		if (it->second.users.has(peer.getFd()))
			it->second.remove(peer);
	}
	this->remove(peer.getFd());
}

void	PeerManager::closeConnection(int fd)
{
	Peer	&peer = (*this)[fd];
	this->closeConnection(peer);
}

void	PeerManager::clear(void)
{
#ifndef NDEBUG
	std::cerr << "Clearing all connections..." << std::endl;
#endif
	for (PeerManager::iterator it = this->begin(); it != this->end();)
	{
#ifndef NDEBUG
	std::cerr << "fd -> " << it->second.getFd() << " ; ";
	std::cerr << "Client -> " << it->second.generatePrefix() << std::endl;
#endif
		if (it->second.close() == -1)
			throw sysCallError("close", strerror(errno));
		this->remove((it++)->second.getFd());
	}
}

Peer	&PeerManager::getByNickname(const std::string &nick)
{
	for (PeerManager::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->second.getNickname() == nick)
			return it->second;
	}
	throw std::out_of_range("PeerManager::getByNickname");
}

bool	PeerManager::hasByNickname(const std::string &nick) const
{
	for (PeerManager::const_iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->second.getNickname() == nick)
			return true;
	}
	return false;
}
