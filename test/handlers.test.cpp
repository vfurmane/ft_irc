#include "catch.hpp"
#include <cstddef>
#include <cstring>

#define private public
#include "handlers.hpp"

ssize_t	g_recv_return;
std::string	g_recv_buf;
ssize_t	recv(int fd, void *buf, size_t n, int flags)
{
	(void)flags;
	(void)n;
	if (fd == -1)
		return -1;
	strcpy(static_cast<char *>(buf), g_recv_buf.c_str());
	return g_recv_return;
}

const std::string	*g_parseInput_arg_input;
void	parseInput(const std::string &input)
{
	g_parseInput_arg_input = &input;
}

TEST_CASE("handleIRCMessage")
{
	g_recv_return = 10;
	g_recv_buf = "HELLOWORLD";

	SECTION("should return -1 if recv returns -1")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		epoll_event		event;
		event.data.fd = 3;

		g_recv_return = -1;

		ssize_t ret = handleIRCMessage(&peer, &event);
		REQUIRE( ret == -1 );
	};

	SECTION("should return -1 if recv returns 0")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		epoll_event		event;
		event.data.fd = 3;

		g_recv_return = 0;

		ssize_t ret = handleIRCMessage(&peer, &event);
		REQUIRE( ret == -1 );
	};

	SECTION("should append the buffer to the message")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		epoll_event		event;
		event.data.fd = 3;

		handleIRCMessage(&peer, &event);
		REQUIRE( peer._message == "HELLOWORLD" );
		handleIRCMessage(&peer, &event);
		REQUIRE( peer._message == "HELLOWORLDHELLOWORLD" );
	};

	SECTION("should clear the message after parsing")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		epoll_event		event;
		event.data.fd = 3;

		handleIRCMessage(&peer, &event);
		handleIRCMessage(&peer, &event);
		g_recv_buf = "DONE\r\n";
		handleIRCMessage(&peer, &event);
		REQUIRE( peer._message.empty() );
	};
};
