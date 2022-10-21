#include <sstream>
#include "mocks.hpp"
#include "catch.hpp"

#define private public
#include "../src/commands/notice/channel.cpp"

TEST_CASE("NOTICE - channel")
{
	Configuration	config;
	Server			server(config);
	PeerManager		&peers = server.peers;
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peers, channels};
	struct sockaddr	addr;
	Peer			&peer = peers.add(3, addr);
	_base_channel	base_channel("general");

	g_send_arg_buf.clear();

	SECTION("when the channel does not exist")
	{
		command_notice_channel(deps, peer, base_channel, "hello world");
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOSUCHCHANNEL(base_channel.getName()).what() + std::string(CRLF)) != g_send_arg_buf.end() );
	};
	SECTION("when the channel exists")
	{
		Peer	&peer1 = peers.add(4, addr);
		peer._nickname = "nick";
		peer1._nickname = "nick1";
		Channel	&channel = peer.createChannel(_base_channel("general"));
		channel.add(peer1);
		command_notice_channel(deps, peer, base_channel, "hello world");
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), NoticeMessage(peer, base_channel.stringify(), "hello world", true).input + std::string(CRLF)) != g_send_arg_buf.end() );
	};
};
