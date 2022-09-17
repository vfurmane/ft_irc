#ifndef HANDLERS_HPP
# define HANDLERS_HPP

# include <iostream>
# include <sys/epoll.h>
# include <sys/socket.h>

# define MAX_READ 63

int	handleTCPMessage(epoll_event *event);

#endif
