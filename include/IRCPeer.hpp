#ifndef IRC_PEER_HPP
# define IRC_PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>
# include "TCPPeer.hpp"
# include "commands.hpp"

class IRCMessage;

class IRCPeer : public TCPPeer
{
	public:
		IRCPeer(const int fd, struct sockaddr &addr);
		IRCPeer(const IRCPeer &obj);
		IRCPeer &operator=(const IRCPeer &rhs);
		~IRCPeer(void);

		void				appendMessage(const char *buffer);
		void				clearMessage(void);
		bool				hasCompleteMessage(void) const;
		const std::string	&getMessage(void) const;
		bool				isRegistered(void) const;
		void				registeration(const std::string &user, int mode, const std::string &realname);

	private:
		std::string		_message;
		std::string		_user;
		std::string		_realname;
		int				_mode;
		bool			_registered;
};

#endif
