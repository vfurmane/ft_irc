#ifndef IRC_PEER_MANAGER_HPP
# define IRC_PEER_MANAGER_HPP

# include <map>
# include "TCPPeerManager.hpp"

class IRCPeer;
class IRCServer;

class IRCPeerManager : public TCPPeerManager
{
	public:
		typedef std::map<int, IRCPeer>::const_iterator	const_iterator;

		IRCPeerManager(IRCServer &server);
		IRCPeerManager(const IRCPeerManager &obj);
		IRCPeerManager &operator=(const IRCPeerManager &rhs);
		~IRCPeerManager(void);

		IRCPeer	&operator[](int fd);

		void			add(int fd, struct sockaddr &addr);
		void			remove(int fd);
		IRCPeer			&get(int fd);
		const_iterator	begin() const;
		const_iterator	end() const;

	private:
		IRCServer				&_server;
		std::map<int, IRCPeer>	_peers;
};

# include "IRCPeer.hpp"
# include "IRCServer.hpp"

#endif
