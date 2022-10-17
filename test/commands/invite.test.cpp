#include "catch.hpp"
#include "mocks.hpp"
#include <sstream>

#define private public
#include "../src/commands/invite.cpp"

TEST_CASE("INVITE")
{
	Configuration	config;
	Server			server(config);
	struct sockaddr	addr;
	Peer			peer(server, 3, addr);
	Message			message(peer, std::string());
	PeerManager		&peers = server.peers;
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peers, channels};
	g_send_arg_buf.clear();

	SECTION("not enough arguments given")
	{
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_invite(message, deps), ERR_NEEDMOREPARAMS );
	}
	SECTION("if channel does not exist")
	{
		peer._username = "test_user";
		message.arguments[0] = "user";
		message.arguments[1] = "#Channel";
		message.argCount = 2;
		REQUIRE( command_invite(message, deps) == 1);
	}
	SECTION ("test with missing #")
	{
		Channel channel(channels, "Channel");
		peer._username = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "user";
		message.arguments[1] = "Channel";
		message.argCount = 2;
		REQUIRE( command_invite(message, deps) == 1);
	}
	SECTION("if the channel exist but peer is not in it")
	{
		Channel	channel(channels, "channel");
		Channel	channel2(channels,"channel2");
		Peer &peer2 = peers.add(4, addr);
		peer2._nickname = "test_user2";
		peer._nickname = "test_user";
		peer.createChannel(channel);
		peer2.createChannel(channel2);
		message.arguments[0] = "test_user2";
		message.arguments[1] = "#channel2";
		message.argCount = 2;
		for (auto it = g_send_arg_buf.begin(); it != g_send_arg_buf.end(); ++it)
		{
			std::cout << *it << std::endl;
		}
		command_invite(message, deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOTONCHANNEL("#channel2").what() + std::string(CRLF)) != g_send_arg_buf.end());
	}
}
