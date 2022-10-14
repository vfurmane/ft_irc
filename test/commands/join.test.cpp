#include <algorithm>
#include <cstddef>
#include <sstream>
#include "IRCErrors.hpp"
#include "mocks.hpp"
#include "catch.hpp"

#define private public
#include "../src/commands/join.cpp"

TEST_CASE("JOIN")
{
	Configuration	config;
	Server			server(config);
	struct sockaddr	addr;
	Peer			peer(server, 3, addr);
	Message			message(peer, std::string());
	PeerManager		peers(server);
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peers, channels};

	g_send_arg_buf.clear();

	SECTION("when not enough arguments were given")
	{
		message.argCount = 0;
		REQUIRE_THROWS_AS( command_join(message, deps), ERR_NEEDMOREPARAMS );
	};
	SECTION("when the channel name's case is different")
	{
		peer._username = "john_doe";
		peer.createChannel(std::string("g[en]ERAL"));
		message.arguments[0] = "#G[En}erAL";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( channels["G{eN]eral"].users.has(peer._username) );
	};
	SECTION("when the channel exists and no key is provided")
	{
		peer._username = "john_doe";
		peer.createChannel(std::string("general"));
		message.arguments[0] = "#general";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._username) );
	};
	SECTION("when the channel exists and a valid key is provided")
	{
		peer._username = "john_doe";
		Channel	&channel = peer.createChannel(std::string("general"));
		channel.setKey("password");
		message.arguments[0] = "#general";
		message.arguments[1] = "password";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._username) );
	};
	SECTION("when the channel exists and an invalid key is provided")
	{
		peer._username = "john_doe";
		Channel	&channel = peer.createChannel(std::string("general"));
		channel.setKey("password");
		message.arguments[0] = "#general";
		message.arguments[1] = "secret";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_BADCHANNELKEY("#general").what() + std::string(CRLF)) != g_send_arg_buf.end() );
	};
	SECTION("when the channel does not exist")
	{
		peer._username = "john_doe";
		message.arguments[0] = "#general";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( server.channels.has("general") );
		REQUIRE( channels["general"].users.has(peer._username) );
	};
	SECTION("with list as parameters")
	{
		peer._username = "john_doe";
		Channel	&general_channel = peer.createChannel(std::string("general"));
		Channel	&ft_irc_channel = peer.createChannel(std::string("ft_irc"));
		general_channel.setKey("password");
		ft_irc_channel.setKey("secret");
		message.arguments[0] = "#general,#ft_irc";
		message.arguments[1] = "password,secret";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._username) );
		REQUIRE( channels["ft_irc"].users.has(peer._username) );
	};
	SECTION("with differing channels and keys length")
	{
		peer._username = "john_doe";
		Channel	&general_channel = peer.createChannel(std::string("general"));
		Channel	&ft_irc_channel = peer.createChannel(std::string("ft_irc"));
		general_channel.setKey("password");
		ft_irc_channel.setKey("secret");
		message.arguments[0] = "#general,#ft_irc";
		message.arguments[1] = "password";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._username) );
		REQUIRE( channels["ft_irc"].users.has(peer._username) );
	};
	SECTION("JOIN 0")
	{
		peer._username = "john_doe";
		Channel	&channel1 = peer.createChannel(std::string("general"));
		Channel	&channel2 = peer.createChannel(std::string("random"));
		channel1.add(peer);
		channel2.add(peer);
		message.arguments[0] = "0";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( !channels["general"].users.has(peer._username) );
		REQUIRE( !channels["random"].users.has(peer._username) );
	};
};
