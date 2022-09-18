#ifndef TCP_PEERMANAGER_HPP
# define TCP_PEERMANAGER_HPP

# include <map>
# include <algorithm>
# include "Peer.hpp"
# include "exception.hpp"

namespace TCP {
	class Server;
};

class PeerManager
{
	public:
		PeerManager(TCP::Server &server);
		PeerManager(const PeerManager &obj);
		PeerManager &operator=(const PeerManager &rhs);
		~PeerManager(void);

		Peer	&operator[](int fd);

		void	add(int fd, struct sockaddr &addr);
		void	remove(int fd);
		Peer	&get(int fd);
		int		acceptConnection(void);
		void	closeConnection(int fd);

	private:
		TCP::Server			&_server;
		std::map<int, Peer> _peers;
};

# include "TCP/Server.hpp"

#endif
