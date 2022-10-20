#include <sstream>
#include "mocks.hpp"
#include "catch.hpp"

#define private public
#include "../src/commands/notice.cpp"

TEST_CASE("NOTICE")
{
	Configuration	config;
	Server			server(config);
	PeerManager		&peers = server.peers;
	struct sockaddr	addr;
	Peer			&peer = peers.add(3, addr);
	Message			message(peer, std::string());
	message.command = "NOTICE";
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peers, channels};

	g_send_arg_buf.clear();

	SECTION("when there is no argument")
	{
		message.argCount = 0;
		REQUIRE_THROWS_AS( command_notice(message, deps), ERR_NEEDMOREPARAMS );
	};
	SECTION("when there is only one argument")
	{
		message.arguments[0] = "nickname";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_notice(message, deps), ERR_NEEDMOREPARAMS );
	};
	SECTION("when the message is empty")
	{
		message.arguments[0] = "nickname";
		message.arguments[1] = "";
		message.argCount = 2;
		REQUIRE_THROWS_AS( command_notice(message, deps), ERR_NEEDMOREPARAMS );
	};
	SECTION("when the message targets a channel")
	{
		Peer	&peer1 = peers.add(4, addr);
		Channel	&channel = peer.createChannel(_base_channel("general"));
		channel.add(peer1);
		message.arguments[0] = "#general";
		message.arguments[1] = "hello";
		message.argCount = 2;
		command_notice(message, deps);
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), NoticeMessage(peer, message.arguments[0], message.arguments[1], true).input + std::string(CRLF)) != g_send_arg_buf.end() );
	};
	SECTION("when the message targets a nickname")
	{
		Peer	&peer1 = peers.add(4, addr);
		peer._nickname = "nick";
		peer1._nickname = "nick1";
		message.arguments[0] = "nick1";
		message.arguments[1] = "hello";
		message.argCount = 2;
		command_notice(message, deps);
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), NoticeMessage(peer, message.arguments[0], message.arguments[1], true).input + std::string(CRLF)) != g_send_arg_buf.end() );
	};
	SECTION("when a list is provided")
	{
		Peer	&peer1 = peers.add(4, addr);
		peer._nickname = "nick";
		peer1._nickname = "nick1";
		Channel	&channel = peer.createChannel(_base_channel("general"));
		channel.add(peer1);
		message.arguments[0] = "#general,nick1";
		message.arguments[1] = "hello";
		message.argCount = 2;
		message.argCount = 2;
		command_notice(message, deps);
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), NoticeMessage(peer, "#general", "hello", true).input + std::string(CRLF)) != g_send_arg_buf.end() );
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), NoticeMessage(peer, "nick1", "hello", true).input + std::string(CRLF)) != g_send_arg_buf.end() );
	};
};
