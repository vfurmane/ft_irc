#include "catch.hpp"
#include <vector>

#define private public
#define protected public
#include "commands.hpp"
#include "IRCErrors.hpp"
#include "IRCMessage.hpp"
#include "IRCPeer.hpp"

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

TEST_CASE("NICK")
{
	SECTION("should throw ERR_NONICKNAMEGIVEN if the no nickname was given")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		IRCMessage		message(peer, std::string());
		Dependencies	deps;

		message._argCount = 0;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_NONICKNAMEGIVEN );
		message._arguments[0] = "";
		message._argCount = 1;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_NONICKNAMEGIVEN );
	};
	SECTION("should set the nickname of the user")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		IRCMessage		message(peer, std::string());
		Dependencies	deps;

		message._arguments[0] = "nickname";
		message._argCount = 1;
		REQUIRE( peer._nickname == "nickname" );
	};
	SECTION("should send a NICK message to all users")
	{
		struct sockaddr	addr;
		IRCPeer			peer(3, addr);
		IRCMessage		message(peer, std::string());
		Dependencies	deps;

		deps.peers.add(4, addr);
		deps.peers.add(5, addr);
		deps.peers.add(6, addr);
		REQUIRE( g_send_arg_sockfd[0] == 4 );
		REQUIRE( g_send_arg_sockfd[1] == 5 );
		REQUIRE( g_send_arg_sockfd[2] == 6 );
	};
};
