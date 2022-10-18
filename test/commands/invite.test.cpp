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
		REQUIRE_THROWS_AS(command_invite(message, deps), ERR_NOTONCHANNEL);
	}
	SECTION("if nickname does not exist")
	{
		Channel	channel(channels, "channel");
		peer._nickname = "test_user";
		peer.createChannel(channel);
		message.arguments[0] = "test_user2";
		message.arguments[1] = "#channel";
		message.argCount = 2;
		REQUIRE_THROWS_AS( command_invite(message, deps), ERR_NOSUCHNICK );
	}
	SECTION("if user already on channel")
	{
		peer._nickname = "test_user";
		Channel	&channel = peer.createChannel(std::string("channel"));
		Peer &peer2 = peers.add(4, addr);
		Message peer2message(peer2, std::string());
		peer2._nickname = "test_user2";
		channel.add(peer2);
		REQUIRE(channel.users.hasByNickname(std::string("test_user2")));
		message.arguments[0] = "test_user2";
		message.arguments[1] = "#channel";
		message.argCount = 2;
		REQUIRE_THROWS_AS( command_invite(message, deps), ERR_USERONCHANNEL );
	}
	SECTION("if channel is invite only and peer is not operator")
	{
		peer._nickname = "test_user";
		Peer &peer2 = peers.add(4, addr);
		peer2._nickname = "test_user2";
		Peer &peer3 = peers.add(5, addr);
		peer3._nickname = "test_user3";
		Channel &channel = peer.createChannel(std::string("channel"));
		channel.add(peer2);
		channel.setFlag(FLAG_INVITE);
		Message message2(peer2, std::string());
		REQUIRE((channel.getFlags() & FLAG_INVITE) == FLAG_INVITE);
		message2.arguments[0] = "test_user3";
		message2.arguments[1] = "#channel";
		message2.argCount = 2;
		REQUIRE_THROWS_AS( command_invite(message2, deps), ERR_CHANOPRIVSNEEDED );
	}
	SECTION("user already on channel")
	{
		peer._nickname = "test_user";
		Peer &peer2 = peers.add(4, addr);
		peer2._nickname = "test_user2";
		Peer &peer3 = peers.add(5, addr);
		peer3._nickname = "test_user3";
		Channel &channel = peer.createChannel(std::string("channel"));
		channel.add(peer2);
		channel.setFlag(FLAG_INVITE);
		REQUIRE((channel.getFlags() & FLAG_INVITE) == FLAG_INVITE);
		message.arguments[0] = "test_user2";
		message.arguments[1] = "#channel";
		message.argCount = 2;
		REQUIRE_THROWS_AS( command_invite(message, deps), ERR_USERONCHANNEL);
	}
	SECTION("should invite correctly")
	{
		peer._nickname = "test_user";
		Peer &peer2 = peers.add(4, addr);
		peer2._nickname = "test_user2";
		Peer &peer3 = peers.add(5, addr);
		peer3._nickname = "test_user3";
		Channel &channel = peer.createChannel(std::string("channel"));
		channel.add(peer2);
		channel.setFlag(FLAG_INVITE);
		REQUIRE((channel.getFlags() & FLAG_INVITE) == FLAG_INVITE);
		message.arguments[0] = "test_user3";
		message.arguments[1] = "#channel";
		message.argCount = 2;
		REQUIRE_NOTHROW( command_invite(message, deps) );
	}
}
