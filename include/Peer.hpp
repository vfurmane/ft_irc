#ifndef PEER_HPP
# define PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>

struct Message;

class Peer
{
	public:
		Peer(const int fd, struct sockaddr &addr);
		Peer(const Peer &obj);
		Peer &operator=(const Peer &rhs);
		~Peer(void);

		int					close(void) const;
		void				appendMessage(const char *buffer);
		void				clearMessage(void);
		bool				hasCompleteMessage(void) const;
		const std::string	&getMessage(void) const;
		bool				isRegistered(void) const;
		void				registration(const std::string &user, const std::string &mode, const std::string &realname);
		void				setNickname(const std::string &new_nick);
		std::string			generatePrefix(void) const;
		void				sendMessage(const Message &message) const;

		char			*getStrAddr(void) const;
		int				getFd(void) const;
		const std::string		&getUsername(void) const;
		const std::string 		&getNickname(void) const;

	private:
		const int				_fd;
		struct sockaddr	_addr;
		std::string		_message;
		std::string		_nickname;
		std::string		_user;
		std::string		_realname;
		std::string		_mode;
		bool			_registered;
};

# include "Message.hpp"

#endif
