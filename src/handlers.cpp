#include "handlers.hpp"

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
#ifndef NDEBUG
		std::cerr << "vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv" << std::endl;
		std::cerr << buffer;
		if (buffer[bytes_read - 1] != '\n')
			std::cerr << "%" << std::endl;
		std::cerr << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
#endif
	}
	return 0;
}
