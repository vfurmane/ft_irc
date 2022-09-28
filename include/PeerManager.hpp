#ifndef PEERMANAGER_HPP
# define PEERMANAGER_HPP

# include <map>
# include <algorithm>
# include "Peer.hpp"
# include "exception.hpp"

class Server;

class PeerManager
{
	public:
		typedef std::map<int, Peer>::const_iterator	const_iterator;

		PeerManager(Server &server);
		PeerManager(const PeerManager &obj);
		PeerManager &operator=(const PeerManager &rhs);
		~PeerManager(void);

		Peer	&operator[](int fd);

		const_iterator	begin(void) const;
		const_iterator	end(void) const;
		void	add(int fd, struct sockaddr &addr);
		void	remove(int fd);
		Peer	&get(int fd);
		int		acceptConnection(void);
		void	closeConnection(int fd);

	private:
		Server				&_server;
		std::map<int, Peer> _peers;
};

# include "Server.hpp"

#endif
