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
	Peer			peer2(server, 4, addr);	
	Message			message(peer, std::string());
	PeerManager		&peers = server.peers;
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
		peer2.createChannel(std::string("g[en]ERAL"));
		message.arguments[0] = "#G[En}erAL";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( channels["G{eN]eral"].users.has(peer._fd) );
	};
	SECTION("when the channel exists and no key is provided")
	{
		peer2.createChannel(std::string("general"));
		message.arguments[0] = "#general";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._fd) );
	};
	SECTION("when the channel exists and the peer is not invited")
	{
		Channel	&channel = peer.createChannel(std::string("general"));
		channel.setFlag(FLAG_INVITE);
		Peer	&peer1 = peers.add(4, addr);
		peer1._nickname = "nick1";
		Message	peer1_message(peer1, std::string());
		peer1_message.arguments[0] = "#general";
		peer1_message.argCount = 1;
		command_join(peer1_message, deps);
		REQUIRE( !channels["general"].users.has(peer1._fd) );
	};
	SECTION("when the channel exists and the peer is invited, but no key was provided")
	{
		Channel	&channel = peer2.createChannel(std::string("general"));
		channel.addInvitation(peer);
		channel.setFlag(FLAG_KEY);
		channel.setKey("password");
		Peer	&peer1 = peers.add(4, addr);
		peer1._nickname = "nick1";
		Message	peer1_message(peer1, std::string());
		channel.addInvitation(peer1);
		peer1_message.arguments[0] = "#general";
		peer1_message.argCount = 1;
		command_join(peer1_message, deps);
		REQUIRE( channels["general"].users.has(peer1._fd) );
	};
	SECTION("when the channel exists and the peer is invited")
	{
		Channel	&channel = peer2.createChannel(std::string("general"));
		channel.setFlag(FLAG_INVITE);
		Peer	&peer1 = peers.add(4, addr);
		peer1._nickname = "nick1";
		Message	peer1_message(peer1, std::string());
		channel.addInvitation(peer1);
		peer1_message.arguments[0] = "#general";
		peer1_message.argCount = 1;
		command_join(peer1_message, deps);
		REQUIRE( channels["general"].users.has(peer1._fd) );
	};
	SECTION("when the channel exists and a valid key is provided")
	{
		Channel	&channel = peer2.createChannel(std::string("general"));
		channel.setFlag(FLAG_KEY);
		channel.setKey("password");
		message.arguments[0] = "#general";
		message.arguments[1] = "password";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._fd) );
	};
	SECTION("when the channel exists and no key was provided (but one is needed)")
	{
		Channel &channel = peer2.createChannel(std::string("general"));
		channel.setFlag(FLAG_KEY);
		channel.setKey("password");
		message.arguments[0] = "#general";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( !channels["general"].users.has(peer._fd) );
	};
	SECTION("when the channel exists and an invalid key is provided")
	{
		Channel	&channel = peer2.createChannel(std::string("general"));
		channel.setFlag(FLAG_KEY);
		channel.setKey("password");
		message.arguments[0] = "#general";
		message.arguments[1] = "secret";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), ERR_BADCHANNELKEY("#general").what() + std::string(CRLF)) != g_send_arg_buf.end() );
	};
	SECTION("when the channel does not exist")
	{
		message.arguments[0] = "#general";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( server.channels.has("general") );
		REQUIRE( channels["general"].users.has(peer._fd) );
	};
	SECTION("with list as parameters")
	{
		Channel	&general_channel = peer2.createChannel(std::string("general"));
		Channel	&ft_irc_channel = peer2.createChannel(std::string("ft_irc"));
		general_channel.setFlag(FLAG_KEY);
		ft_irc_channel.setFlag(FLAG_KEY);
		general_channel.setKey("password");
		ft_irc_channel.setKey("secret");
		message.arguments[0] = "#general,#ft_irc";
		message.arguments[1] = "password,secret";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._fd) );
		REQUIRE( channels["ft_irc"].users.has(peer._fd) );
	};
	SECTION("with differing channels and keys length, only one key input")
	{
		Channel	&general_channel = peer2.createChannel(std::string("general"));
		Channel	&ft_irc_channel = peer2.createChannel(std::string("ft_irc"));
		general_channel.setFlag(FLAG_KEY);
		ft_irc_channel.setFlag(FLAG_KEY);
		general_channel.setKey("password");
		ft_irc_channel.setKey("secret");
		message.arguments[0] = "#general,#ft_irc";
		message.arguments[1] = "password";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._fd) );
		REQUIRE( !channels["ft_irc"].users.has(peer._fd) );
	};
	SECTION("with differing channels and keys length, one key correct one wrong")
	{
		Channel	&general_channel = peer2.createChannel(std::string("general"));
		Channel	&ft_irc_channel = peer2.createChannel(std::string("ft_irc"));
		general_channel.setFlag(FLAG_KEY);
		ft_irc_channel.setFlag(FLAG_KEY);
		general_channel.setKey("password");
		ft_irc_channel.setKey("secret");
		message.arguments[0] = "#general,#ft_irc";
		message.arguments[1] = "password,pass";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._fd) );
		REQUIRE( !channels["ft_irc"].users.has(peer._fd) );
	};
	SECTION("with differing channels and keys length, both correct")
	{
		Channel	&general_channel = peer2.createChannel(std::string("general"));
		Channel	&ft_irc_channel = peer2.createChannel(std::string("ft_irc"));
		general_channel.setFlag(FLAG_KEY);
		ft_irc_channel.setFlag(FLAG_KEY);
		general_channel.setKey("password");
		ft_irc_channel.setKey("secret");
		message.arguments[0] = "#general,#ft_irc";
		message.arguments[1] = "password,secret";
		message.argCount = 2;
		command_join(message, deps);
		REQUIRE( channels["general"].users.has(peer._fd) );
		REQUIRE( channels["ft_irc"].users.has(peer._fd) );
	};
	SECTION("JOIN 0")
	{
		Channel	&channel1 = peer2.createChannel(std::string("general"));
		Channel	&channel2 = peer2.createChannel(std::string("random"));
		channel1.add(peer);
		channel2.add(peer);
		message.arguments[0] = "0";
		message.argCount = 1;
		command_join(message, deps);
		REQUIRE( !channels["general"].users.has(peer._fd) );
		REQUIRE( !channels["random"].users.has(peer._fd) );
	};
};
