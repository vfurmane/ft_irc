#include "catch.hpp"
#include "mocks.cpp"
#include <vector>

#define private public
#define protected public
#include "commands.hpp"
#include "IRCErrors.hpp"
#include "Message.hpp"
#include "Peer.hpp"


TEST_CASE("NICK")
{
	SECTION("should throw ERR_NONICKNAMEGIVEN if the no nickname was given")
	{
		struct sockaddr	addr;
		Peer			peer(3, addr);
		Message			message(peer, std::string());
		Server			server((char *)"8080");
		PeerManager		peers(server);
		Dependencies	deps = {peers};

		message.argCount = 0;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_NONICKNAMEGIVEN );
		message.arguments[0] = "";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_NONICKNAMEGIVEN );
	};
	SECTION("should set the nickname of the user")
	{
		struct sockaddr	addr;
		Peer			peer(3, addr);
		Message			message(peer, std::string());
		Server			server((char *)"8080");
		PeerManager		peers(server);
		Dependencies	deps = {peers};

		message.arguments[0] = "nickname";
		message.argCount = 1;
		command_nick(message, deps);
		REQUIRE( peer._nickname == "nickname" );
	};
	SECTION("should send a NICK message to all users")
	{
		struct sockaddr	addr;
		Peer			peer(3, addr);
		Message			message(peer, std::string());
		Server			server((char *)"8080");
		PeerManager		peers(server);
		Dependencies	deps = {peers};

		message.arguments[0] = "nickname";
		message.argCount = 1;
		deps.peers.add(4, addr);
		deps.peers.add(5, addr);
		deps.peers.add(6, addr);
		command_nick(message, deps);
		REQUIRE( g_send_arg_sockfd[0] == 4 );
		REQUIRE( g_send_arg_sockfd[1] == 5 );
		REQUIRE( g_send_arg_sockfd[2] == 6 );
	};
};
