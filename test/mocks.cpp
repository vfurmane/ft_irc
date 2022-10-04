#ifndef TEST_MOCKS_CPP
# define TEST_MOCKS_CPP

# include "mocks.hpp"

int g_close_return = 0;
int	close(int fd)
{
	(void)fd;
	return g_close_return;
}

int g_bind_return = 0;
int	bind(int fd, const struct sockaddr *addr, socklen_t len)
{
	(void)fd;
	(void)addr;
	(void)len;
	return g_bind_return;
}

int	g_getaddrinfo_return = 0;
int getaddrinfo(const char *__restrict name, const char *__restrict service, const struct addrinfo *__restrict req, struct addrinfo **__restrict pai)
{
	(void)name;
	(void)service;
	(void)req;
	(void)pai;
	return g_getaddrinfo_return;
}

int g_setsockopt_return = 0;
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{
	(void)sockfd;
	(void)level;
	(void)optname;
	(void)optval;
	(void)optlen;
	return g_setsockopt_return;
}

int g_socket_return = 3;
int socket(int domain, int type, int protocol)
{
	(void)domain;
	(void)type;
	(void)protocol;
	return g_socket_return;
}

void freeaddrinfo(struct addrinfo *res)
{
	(void)res;
}

ssize_t 			g_send_return = 0;
std::vector<int>	g_send_arg_sockfd;
ssize_t send(int sockfd, const void *buf, size_t len, int flags)
{
	(void)buf;
	(void)len;
	(void)flags;
	g_send_arg_sockfd.push_back(sockfd);
	return g_send_return;
}

#endif
