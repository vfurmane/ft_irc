#ifndef HANDLERS_HPP
# define HANDLERS_HPP

# include <sys/epoll.h>
# include <sys/socket.h>
# include "IRCPeer.hpp"
# include "TCPPeer.hpp"

# ifndef NDEBUG
#  include <iostream>
# endif

# define MAX_READ 63

int	handleIRCMessage(IRCPeer &peer, epoll_event *event);
int	handleTCPMessage(TCPPeer &peer, epoll_event *event);

#endif
