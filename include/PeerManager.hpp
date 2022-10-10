#ifndef PEERMANAGER_HPP
# define PEERMANAGER_HPP

# include <map>
# include <algorithm>
# include <stdexcept>
# include "exception.hpp"
# include "utils.hpp"

class Peer;
class Server;

class PeerManager
{
	public:
		typedef std::map<int, Peer>::iterator		iterator;
		typedef std::map<int, Peer>::const_iterator	const_iterator;

		PeerManager(Server &server);
		PeerManager(const PeerManager &obj);
		PeerManager &operator=(const PeerManager &rhs);
		~PeerManager(void);

		Peer	&operator[](int fd);

		iterator		begin(void);
		iterator		end(void);
		const_iterator	begin(void) const;
		const_iterator	end(void) const;
		void			clear(void);
		std::pair<PeerManager::iterator, bool>	add(int fd, struct sockaddr &addr);
		void	remove(int fd);
		Peer	&get(int fd);
		bool	containsNickname(const std::string &nick) const;
		int		acceptConnection(void);
		void	closeConnection(int fd);

	private:
		Server				&_server;
		std::map<int, Peer> _peers;
};

# include "Peer.hpp"
# include "Server.hpp"

#endif
