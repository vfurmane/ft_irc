#include "handlers.hpp"

#include <stdio.h> // TODO Remove le header

void	handleTCPMessage(epoll_event *event)
{
	int		bytes_read;
	char	buffer[MAX_READ + 1];
	
	bytes_read = recv(event->data.fd, buffer, MAX_READ, 0);
	buffer[bytes_read] = '\0';
	printf("%s", buffer); // DEBUG
}
