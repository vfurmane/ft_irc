#include <sstream>
#include "mocks.hpp"
#include "catch.hpp"

#define private public
#include "../src/commands/topic.cpp"

TEST_CASE("TOPIC")
{
	Configuration	config;
	Server			server(config);
	PeerManager		&peers = server.peers;
	struct sockaddr	addr;
	Peer			&peer = peers.add(3, addr);
	Message			message(peer, std::string());
	message.command = "TOPIC";
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peers, channels};

	g_send_arg_buf.clear();

	SECTION("when there is no argument")
	{
		message.argCount = 0;
		REQUIRE_THROWS_AS( command_topic(message, deps), ERR_NEEDMOREPARAMS );
	};
	SECTION("when the topic is asked (1 argument)")
	{
		Channel	&channel = peer.createChannel(_base_channel("general"));
		message.arguments[0] = "#general";
		message.argCount = 1;

		SECTION("when the topic is not set")
		{
			command_topic(message, deps);
			REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), RPL_NOTOPIC(peer, channel).input + std::string(CRLF)) != g_send_arg_buf.end() );
		};
		SECTION("when the topic is set")
		{
			channel.setTopic("this is the topic of the channel");
			command_topic(message, deps);
			REQUIRE( std::find(g_send_arg_buf.begin(), g_send_arg_buf.end(), RPL_TOPIC(peer, channel).input + std::string(CRLF)) != g_send_arg_buf.end() );
		};
	};
	SECTION("when the topic is set (2 arguments)")
	{
		Peer	peer1(server, 4, addr);
		Channel	&channel = peer.createChannel(_base_channel("general"));
		channel.add(peer1);
		message.arguments[0] = "#general";
		message.arguments[1] = "this is the topic of the channel";
		message.argCount = 2;

		SECTION("when the user is not on the channel")
		{
			channels.add("random");
			message.arguments[0] = "#random";
			REQUIRE_THROWS_AS( command_topic(message, deps), ERR_NOTONCHANNEL );
		};
		SECTION("when the channel requires advanced permission")
		{
			channel.setFlag(FLAG_TOPIC);

			SECTION("when the user is a basic user")
			{
				channel._creator->setStatus(CHANNEL_USER);
				REQUIRE_THROWS_AS( command_topic(message, deps), ERR_CHANOPRIVSNEEDED );
			};
			SECTION("when the user is channel operator")
			{
				channel._creator->setStatus(CHANNEL_OPERATOR);
				command_topic(message, deps);
				REQUIRE( channel.getTopic() == message.arguments[1] );
				REQUIRE( static_cast<UserManager::size_type>(std::count(g_send_arg_buf.begin(), g_send_arg_buf.end(), TopicMessage(peer, channel, true).input + std::string(CRLF))) == channel.users.size() );
			};
			SECTION("when the user is channel creator")
			{
				command_topic(message, deps);
				REQUIRE( channel.getTopic() == message.arguments[1] );
				REQUIRE( static_cast<UserManager::size_type>(std::count(g_send_arg_buf.begin(), g_send_arg_buf.end(), TopicMessage(peer, channel, true).input + std::string(CRLF))) == channel.users.size() );
			};
		};
		SECTION("when the channel requires no permission")
		{
			SECTION("when the user is a basic user")
			{
				channel._creator->setStatus(CHANNEL_USER);
				command_topic(message, deps);
				REQUIRE( channel.getTopic() == message.arguments[1] );
				REQUIRE( static_cast<UserManager::size_type>(std::count(g_send_arg_buf.begin(), g_send_arg_buf.end(), TopicMessage(peer, channel, true).input + std::string(CRLF))) == channel.users.size() );
			};
			SECTION("when the user is channel operator")
			{
				channel._creator->setStatus(CHANNEL_OPERATOR);
				command_topic(message, deps);
				REQUIRE( channel.getTopic() == message.arguments[1] );
				REQUIRE( static_cast<UserManager::size_type>(std::count(g_send_arg_buf.begin(), g_send_arg_buf.end(), TopicMessage(peer, channel, true).input + std::string(CRLF))) == channel.users.size() );
			};
			SECTION("when the user is channel creator")
			{
				command_topic(message, deps);
				REQUIRE( channel.getTopic() == message.arguments[1] );
				REQUIRE( static_cast<UserManager::size_type>(std::count(g_send_arg_buf.begin(), g_send_arg_buf.end(), TopicMessage(peer, channel, true).input + std::string(CRLF))) == channel.users.size() );
			};
		};
	};
};
