#include "handlers.hpp"

#include <stdio.h> // TODO Remove le header

int	handleTCPMessage(epoll_event *event)
{
	int		bytes_read;
	char	buffer[MAX_READ + 1];
	
	bytes_read = recv(event->data.fd, buffer, MAX_READ, 0);
	if (bytes_read == 0)
		return -1;
	else
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer); // DEBUG
	}
	return 0;
}
