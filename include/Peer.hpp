#ifndef PEER_HPP
# define PEER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdint.h>
# include <string>
# include <sys/socket.h>
# include <unistd.h>
# include "IRCErrors.hpp"
# include "utils.hpp"

class _base_channel;
class Channel;
struct Message;
class Server;

class Peer
{
	public:
		Peer(Server &server, const int fd, const struct sockaddr &addr);
		Peer(const Peer &obj);
		Peer &operator=(const Peer &rhs);
		~Peer(void);

		Channel				&createChannel(const _base_channel &base_channel);
		int					close(void) const;
		void				appendMessage(const char *buffer);
		void				clearMessage(void);
		bool				hasCompleteMessage(void) const;
		const std::string	&getMessage(void) const;
		void				setUsername(const std::string &username);
		void				setMode(const std::string &mode);
		void				setRealName(const std::string &realname);
		bool				hasAllFields(void) const;
		bool				isRegistered(void) const;
		int					registration(const std::string &password = std::string());
		void				setNickname(const std::string &new_nick);
		void				setPassword(const std::string &new_password);
		std::string			generatePrefix(void) const;
		void				sendMessage(const Message &message) const;
		void				sendMessage(const AIRCError &error) const;

		char			*getStrAddr(void) const;
		int				getFd(void) const;
		const std::string		&getUsername(void) const;
		const std::string 		&getNickname(void) const;
		const std::string		&getPassword(void) const;

		Server	&server;

	private:
		const int				_fd;
		struct sockaddr	_addr;
		std::string		_message;
		std::string		_nickname;
		std::string		_username;
		std::string		_realname;
		std::string		_mode;
		std::string		_password;
		bool			_registered;
};

# include "Channel.hpp"
# include "Message.hpp"
# include "Server.hpp"

#endif
