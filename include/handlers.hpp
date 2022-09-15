#ifndef HANDLERS_HPP
# define HANDLERS_HPP

# include <sys/epoll.h>
# include <sys/socket.h>

# define MAX_READ 63

void	handleTCPMessage(epoll_event *event);

#endif
