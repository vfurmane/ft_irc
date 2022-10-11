#include "catch.hpp"
#include <sstream>

#define private public
#include "../src/commands/part.cpp"

TEST_CASE("PART")
{
	Configuration	config;
	Server			server(config);
	struct sockaddr	addr;
	Peer			peer(server, 3, addr);
	Message			message(peer, std::string());
	PeerManager		peers(server);
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peers, channels};

	SECTION("not enough arguments given")
	{
		message.argCount = 0;
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NEEDMOREPARAMS );
	}
	SECTION("no such channel")
	{
		peer._user = "test_user";
		message.arguments[0] = "#secret";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOSUCHCHANNEL );
	}
	SECTION("user not on channel")
	{
		Channel channel("channel");
		Peer	test_peer(server, 4, addr);
		test_peer._user = "valentin";
		test_peer.createChannel(channel);
		message.arguments[0] = "channel";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOTONCHANNEL );
	}
	SECTION("user on channel")
	{
		Channel channel("channel");
		peer._user = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "channel";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
	}
}
