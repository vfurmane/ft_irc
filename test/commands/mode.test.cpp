#include "catch.hpp"
#include <sstream>

#define private public
#define protected public
#include "commands.hpp"
#include "IRCErrors.hpp"
#include "Message.hpp"
#include "Peer.hpp"

#include "../src/commands/mode.cpp"

TEST_CASE("MODE")
{
	SECTION("should throw an error if argcount < 2")
	{	
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};

		message.argCount = 0;
		REQUIRE_THROWS_AS( command_mode(message, deps), ERR_NEEDMOREPARAMS );
		message.arguments[0] = "hello";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_mode(message, deps), ERR_NEEDMOREPARAMS );
	};
	SECTION("should return immediately if the channel prefix is different from : #&!")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};
	
		message.argCount = 2;
		message.arguments[0] = "general";

		REQUIRE( command_mode(message, deps) == 1 );
	};
	SECTION("should throw an error if the flag sent is not recognized")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};

		peer._username = "john_doe";
		Channel &channel = channels.add("general");
		channel.add(peer);
		message.argCount = 2;
		message.arguments[0] = "#general";
		message.arguments[1] = "+z";

		REQUIRE_THROWS_AS( command_mode(message, deps), ERR_UNKNOWNMODE );
	};
	SECTION("should throw an error if there are multiple _status and at least one if incorrect")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};

		peer._username = "john_doe";
		Channel &channel = channels.add("general");
		User &user = channel.add(peer);
		user._status = CHANNEL_OPERATOR;
		message.argCount = 2;
		message.arguments[0] = "#general";
		message.arguments[1] = "+ioz";

		REQUIRE_THROWS_AS( command_mode(message, deps), ERR_UNKNOWNMODE );
	};
	SECTION("should throw an error if the user is not operator or creator and try to change _status")
	{	
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};

		peer._username = "john_doe";
		Channel &channel = channels.add("general");
		User &user = channel.add(peer);
		user._status = CHANNEL_USER;
		message.argCount = 2;
		message.arguments[0] = "#general";
		message.arguments[1] = "+i";

		REQUIRE_THROWS_AS( command_mode(message, deps), ERR_CHANOPRIVSNEEDED );
	};
	SECTION("should correctly change the channel _status when key is used")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};

		peer._username = "john_doe";
		Channel &channel = channels.add("general");
		User &user = channel.add(peer);
		user._status = CHANNEL_OPERATOR;
		message.argCount = 3;
		message.arguments[0] = "#general";
		message.arguments[1] = "+k";
		message.arguments[2] = "password";

		command_mode(message, deps);
		REQUIRE ( channel._key == "password");
		REQUIRE ( channel._flags == FLAG_KEY );
	
		message.argCount = 2;
		message.arguments[0] = "#general";
		message.arguments[1] = "-k";
		command_mode(message, deps);

		REQUIRE ( channel._key == "" );
		REQUIRE ( channel._flags == 0 );
	};
	SECTION("should correctly change the user _status when operator is used")
	{	
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer1(server, 3, addr);
		Peer			peer2(server, 4, addr);
		Message			message(peer1, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};

		peer1._username = "john_doe";
		peer2._username = "wruce_bayne";
		Channel &channel = channels.add("general");
		User &user1 = channel.add(peer1);
		User &user2 = channel.add(peer2);
		user1._status = CHANNEL_CREATOR;
		user2._status = CHANNEL_USER;
		message.argCount = 3;
		message.arguments[0] = "#general";
		message.arguments[1] = "+o";
		message.arguments[2] = "wruce_bayne";
		command_mode(message, deps);

		REQUIRE ( user2._status == CHANNEL_OPERATOR );

		message.argCount = 3;
		message.arguments[0] = "#general";
		message.arguments[1] = "-o";
		message.arguments[2] = "wruce_bayne";
		command_mode(message, deps);

		REQUIRE ( user2._status == CHANNEL_USER );
	};
	SECTION("should prevent the change of the operator flag if author is not creator")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer1(server, 3, addr);
		Peer			peer2(server, 4, addr);
		Message			message(peer1, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	&channels = server.channels;
		Dependencies	deps = {config, peermanager, channels};

		peer1._username = "john_doe";
		peer2._username = "wruce_bayne";
		Channel &channel = channels.add("general");
		User &user1 = channel.add(peer1);
		User &user2 = channel.add(peer2);
		user1._status = CHANNEL_OPERATOR;
		user2._status = CHANNEL_OPERATOR;
		message.argCount = 3;
		message.arguments[0] = "#general";
		message.arguments[1] = "-o";
		message.arguments[2] = "wruce_bayne";
		command_mode(message, deps);

		REQUIRE ( user2._status == CHANNEL_OPERATOR );
	};
};
