#include "catch.hpp"
#include <sstream>

#define private public
#define protected public
#include "commands.hpp"
#include "IRCErrors.hpp"
#include "Message.hpp"
#include "Peer.hpp"

#include "../src/commands/kick.cpp"

TEST_CASE("KICK")
{
	SECTION("should throw an error if there are not enough arguments")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Peer			peer2(server, 4, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Channel &channel = peer.createChannel(std::string("channel"));
		Dependencies	deps = {config, peermanager, channels};

		message.argCount = 0;
		REQUIRE_THROWS_AS( command_kick(message, deps), ERR_NEEDMOREPARAMS );
		message.arguments[0] = "#general";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_kick(message, deps), ERR_NEEDMOREPARAMS );
		message.arguments[1] = "john_doe";
		peer._username = "wruce_bayne";
		peer2._username = "john_doe";
		message.argCount = 2;
		REQUIRE( command_kick(message,deps) == 1 );
	}
};
