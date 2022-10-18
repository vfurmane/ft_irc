#ifndef PEERMANAGER_HPP
# define PEERMANAGER_HPP

# include <map>
# include <algorithm>
# include <stdexcept>
# include "Manager.hpp"
# include "exception.hpp"
# include "utils.hpp"

class Peer;
class Server;

class PeerManager : public Manager<int, Peer>
{
	public:
		PeerManager(Server &server);
		PeerManager(const PeerManager &obj);
		PeerManager &operator=(const PeerManager &rhs);
		~PeerManager(void);

		void	clear(void);
		Peer	&add(int fd, struct sockaddr &addr);
		bool	containsNickname(const std::string &nick) const;
		int		acceptConnection(void);
		void	closeConnection(Peer &peer);
		void	closeConnection(int fd);

		Peer	&getByNickname(const std::string &nick);
		bool	hasByNickname(const std::string &nick) const;

	private:
		Server				&_server;
};

# include "Peer.hpp"
# include "Server.hpp"

#endif
