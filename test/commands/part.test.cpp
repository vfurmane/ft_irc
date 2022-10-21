#include "catch.hpp"
#include "mocks.hpp"
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
		peer._username = "test_user";
		message.arguments[0] = "#secret";
		message.argCount = 1;
		command_part(message, deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOSUCHCHANNEL(peer._nickname, "#secret").what() + std::string(CRLF)) != g_send_arg_buf.end());
	}
	SECTION("should work with complex channel name #1")
	{
		ChannelManager	channels;
		Channel			channel(channels, "general");
		peer._username = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "#Channel";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
	}
	SECTION("should work with complex channel name #2")
	{
		ChannelManager	channels;
		Channel			channel(channels, "this_is_the_best_channel");
		peer._username = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "#tHIs_iS_tHe_beSt_chaNNEl";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
	}
	SECTION("should remove the user from channel")
	{
		ChannelManager	channels;
		peer._username = "test_user";
		Channel &channel = peer.createChannel(_base_channel("channel"));
		Peer	peer1(server, 4, addr);
		channel.add(peer1);
		message.arguments[0] = "#channel";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
		command_part(message, deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOTONCHANNEL(peer._nickname, "#channel").what() + std::string(CRLF)) != g_send_arg_buf.end());
	}
	SECTION("user not on channel")
	{
		ChannelManager	channels;
		Channel			channel(channels, "channel");
		Peer	test_peer(server, 4, addr);
		test_peer._username = "valentin";
		test_peer.createChannel(channel);
		message.arguments[0] = "#channel";
		message.argCount = 1;
		command_part(message, deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOTONCHANNEL(peer._nickname, "#channel").what() + std::string(CRLF)) != g_send_arg_buf.end());
	}
	SECTION("user on channel")
	{
		ChannelManager	channels;
		Channel			channel(channels, "channel");
		peer._username = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "#channel";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
	}
	SECTION("should part from a list of channel")
	{
		ChannelManager	channels;
		peer._username = "test_user";
		Channel &channel1 = peer.createChannel(_base_channel("channel1"));
		Channel &channel2 = peer.createChannel(_base_channel("channel2"));
		Channel &channel3 = peer.createChannel(_base_channel("channel3"));
		Channel &channel4 = peer.createChannel(_base_channel("channel4"));
		Peer	peer1(server, 4, addr);
		channel1.add(peer1);
		channel2.add(peer1);
		channel3.add(peer1);
		channel4.add(peer1);
		message.arguments[0] = "#channel1,#channel2,#channel4,#channel3";
		message.argCount = 1;
		REQUIRE_NOTHROW( command_part(message, deps) );
		message.arguments[0] = "#channel1";
		command_part(message,deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOTONCHANNEL(peer._nickname, "#channel1").what() + std::string(CRLF)) != g_send_arg_buf.end());
		message.arguments[0] = "#channel2";
		command_part(message,deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOTONCHANNEL(peer._nickname, "#channel2").what() + std::string(CRLF)) != g_send_arg_buf.end());
		message.arguments[0] = "#channel3";
		command_part(message,deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOTONCHANNEL(peer._nickname, "#channel3").what() + std::string(CRLF)) != g_send_arg_buf.end());
		message.arguments[0] = "#channel4";
		command_part(message,deps);
		REQUIRE(std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOTONCHANNEL(peer._nickname, "#channel4").what() + std::string(CRLF)) != g_send_arg_buf.end());
	}
}
