#include "catch.hpp"
#include <cstddef>
#include <cstring>

#define private public
#include "handlers.hpp"

ssize_t	g_recv_return;
ssize_t	recv(int fd, void *buf, size_t n, int flags)
{
	const char	str[] = "HELLOWORLD";

	(void)flags;
	(void)n;
	if (fd == -1)
		return -1;
	strcpy(static_cast<char *>(buf), str);
	return g_recv_return;
}

TEST_CASE("handleIRCMessage")
{
	SECTION("should return -1 if recv returns -1")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		epoll_event		event;

		event.data.fd = 3;
		g_recv_return = -1;

		ssize_t ret = handleIRCMessage(peer, &event);
		REQUIRE( ret == -1 );
	};

	SECTION("should return -1 if recv returns 0")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		epoll_event		event;

		event.data.fd = 3;
		g_recv_return = 0;

		ssize_t ret = handleIRCMessage(peer, &event);
		REQUIRE( ret == -1 );
	};

	SECTION("should append the buffer to the message")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		epoll_event		event;

		event.data.fd = 3;
		g_recv_return = 10;

		handleIRCMessage(peer, &event);
		REQUIRE( peer._message == "HELLOWORLD" );
		handleIRCMessage(peer, &event);
		REQUIRE( peer._message == "HELLOWORLDHELLOWORLD" );
	};
};
