#ifndef IRC_PEER_HPP
# define IRC_PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
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
		void				registration(const std::string &user, const std::string &mode, const std::string &realname);
		void				setNickname(const std::string &new_nick);
		void				sendMessage(const IRCMessage &message) const;

	private:
		std::string		_message;
		std::string		_nickname;
		std::string		_user;
		std::string		_realname;
		std::string		_mode;
		bool			_registered;
};

# include "IRCMessage.hpp"

#endif
