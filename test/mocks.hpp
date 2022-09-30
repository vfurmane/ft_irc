#ifndef TEST_MOCKS_HPP
# define TEST_MOCKS_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <vector>

extern int				g_bind_return;
extern int 				g_getaddrinfo_return;
extern int 				g_setsockopt_return;
extern int 				g_socket_return;
extern ssize_t 			g_send_return;
extern std::vector<int>	g_send_arg_sockfd;

#endif
