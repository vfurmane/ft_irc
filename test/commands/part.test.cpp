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
	SECTION("should work with complex channel name #1")
	{
		Channel channel("channel");
		peer._user = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "#Channel";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
	}
	SECTION("should remove the user from channel")
	{
		Channel channel("channel");
		peer._user = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "channel";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOTONCHANNEL );
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
	SECTION("should part from a list of channel")
	{
		Channel channel1("channel1");
		Channel channel2("channel2");
		Channel channel3("channel3");
		Channel channel4("channel4");
		peer._user = "test_user";
		peer.createChannel(channel1);
		peer.createChannel(channel2);
		peer.createChannel(channel3);
		peer.createChannel(channel4);
		message.arguments[0] = "channel1,channel2,channel4,channel3";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOTONCHANNEL );
		message.arguments[0] = "channel1";
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOTONCHANNEL );
		message.arguments[0] = "channel2";
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOTONCHANNEL );
		message.arguments[0] = "channel3";
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOTONCHANNEL );
		message.arguments[0] = "channel4";
		REQUIRE_THROWS_AS( command_part(message, deps), ERR_NOTONCHANNEL );
	}
}
