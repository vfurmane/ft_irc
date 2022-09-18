#ifndef HANDLERS_HPP
# define HANDLERS_HPP

# include <sys/epoll.h>
# include <sys/socket.h>

# ifndef NDEBUG
#  include <iostream>
# endif

# define MAX_READ 63

int	handleTCPMessage(epoll_event *event);

#endif
