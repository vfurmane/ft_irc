#include "catch.hpp"
#include <sstream>

#define private public
#define protected public
#include "commands.hpp"
#include "IRCErrors.hpp"
#include "Message.hpp"
#include "Peer.hpp"

#include "../src/commands/kick.cpp"

TEST_CASE("KICK")
{
	struct sockaddr	addr;
	Configuration	config;
	Server			server(config);
	Peer			peer(server, 3, addr);
	Peer			peer2(server, 4, addr);
	Message			message(peer, std::string());
	PeerManager		&peermanager = server.peers;
	ChannelManager	&channels = server.channels;
	Dependencies	deps = {config, peermanager, channels};

	SECTION("should throw an error if there are no arguments")
	{
		message.argCount = 0;
		REQUIRE_THROWS_AS( command_kick(message, deps), ERR_NEEDMOREPARAMS );
	}
	SECTION("should throw an error if there is only one argument")
	{
		message.arguments[0] = "#general";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_kick(message, deps), ERR_NEEDMOREPARAMS );
	}
	SECTION("should throw an error if the channel doesn't exist")
	{
		Channel &channel = peer.createChannel(_base_channel("general"));
		message.arguments[0] = "#doesntexist";
		message.arguments[1] = "john_doe";
		message.argCount = 2;
		peer._nickname = "wruce_bayne";
		peer2._nickname = "john_doe";
		channel.add(peer2);

		REQUIRE_THROWS_AS( command_kick(message, deps), ERR_NOSUCHCHANNEL );
	}
	SECTION("should throw an error if the author is not in the channel")
	{
		Channel &channel = peer.createChannel(_base_channel("general"));
		Channel &channel2 = peer2.createChannel(_base_channel("general2"));
		message.arguments[0] = "#general2";
		message.arguments[1] = "john_doe";
		message.argCount = 2;
		peer._nickname = "wruce_bayne";
		peer2._nickname = "john_doe";
		channel.add(peer2);
		channel2.add(peer2);

		REQUIRE_THROWS_AS( command_kick(message, deps), ERR_NOTONCHANNEL );
	}
	SECTION("should throw an error if the author is not at least a channel operator")
	{
		Channel &channel = peer.createChannel(_base_channel("general"));
		message.arguments[0] = "#general";
		message.arguments[1] = "john_doe";
		message.argCount = 2;
		peer._nickname = "wruce_bayne";
		peer2._nickname = "john_doe";
		channel.users.getByNickname("wruce_bayne").setStatus(CHANNEL_USER);
		channel.add(peer2);

		REQUIRE_THROWS_AS( command_kick(message,deps), ERR_CHANOPRIVSNEEDED );
	}
	SECTION("should prevent a channel operator from kicking a channel creator")
	{
		Channel &channel = peer.createChannel(_base_channel("general"));
		message.arguments[0] = "#general";
		message.arguments[1] = "john_doe";
		message.argCount = 2;
		peer._nickname = "wruce_bayne";
		peer2._nickname = "john_doe";
		channel.add(peer2);
		channel.users.getByNickname("wruce_bayne").setStatus(CHANNEL_OPERATOR);
		channel.users.getByNickname("john_doe").setStatus(CHANNEL_CREATOR);
		command_kick(message, deps);

		REQUIRE(channel.users.hasByNickname("john_doe") == true);
	}
	SECTION("should work properly if the author is of a higher status than the target and in the same channel")
	{
		Channel &channel = peer.createChannel(_base_channel("general"));
		message.arguments[0] = "#general";
		message.arguments[1] = "john_doe";
		message.argCount = 2;
		peer._nickname = "wruce_bayne";
		peer2._nickname = "john_doe";
		channel.add(peer2);
		REQUIRE( command_kick(message, deps) == 1 );
		REQUIRE_THROWS_AS( command_kick(message, deps), ERR_USERNOTINCHANNEL );
	}
};
