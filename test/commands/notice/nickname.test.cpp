#include <sstream>
#include "mocks.hpp"
#include "catch.hpp"

#define private public
#include "../src/commands/notice/nickname.cpp"

TEST_CASE("NOTICE - nickname")
{
	Configuration	config;
	Server			server(config);
	PeerManager		&peers = server.peers;
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peers, channels};
	struct sockaddr	addr;
	Peer			&peer = peers.add(3, addr);

	g_send_arg_buf.clear();

	SECTION("when the nickname is not in use")
	{
		command_notice_nickname(deps, peer, "nick1", "hello world");
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_NOSUCHNICK("nick1").what() + std::string(CRLF)) != g_send_arg_buf.end() );
	};
	SECTION("when the nickname is in use")
	{
		Peer	&peer1 = peers.add(4, addr);
		peer._nickname = "nick";
		peer1._nickname = "nick1";
		command_notice_nickname(deps, peer, "nick1", "hello world");
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), NoticeMessage(peer, "nick1", "hello world", true).input + std::string(CRLF)) != g_send_arg_buf.end() );
	};
};
