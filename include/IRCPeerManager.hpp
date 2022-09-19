#ifndef TCP_PEERMANAGER_HPP
# define TCP_PEERMANAGER_HPP

# include <map>
# include <algorithm>
# include "TCPPeer.hpp"
# include "exception.hpp"

class TCPServer;

class TCPPeerManager
{
	public:
		TCPPeerManager(TCPServer &server);
		TCPPeerManager(const TCPPeerManager &obj);
		TCPPeerManager &operator=(const TCPPeerManager &rhs);
		~TCPPeerManager(void);

		TCPPeer	&operator[](int fd);

		void	add(int fd, struct sockaddr &addr);
		void	remove(int fd);
		TCPPeer	&get(int fd);
		int		acceptConnection(void);
		void	closeConnection(int fd);

	private:
		TCPServer				&_server;
		std::map<int, TCPPeer> _peers;
};

# include "TCPServer.hpp"

#endif
