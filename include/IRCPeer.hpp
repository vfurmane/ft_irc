#ifndef IRC_PEER_HPP
# define IRC_PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>
# include "TCPPeer.hpp"

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

	private:
		std::string		_message;
};

#endif
