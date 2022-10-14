#include "catch.hpp"
#include <sstream>
#include <vector>

#define private public
#define protected public
#include "commands.hpp"
#include "IRCErrors.hpp"
#include "Message.hpp"
#include "Peer.hpp"

#include "../src/commands/user.cpp"

TEST_CASE("USER")
{
	SECTION("should throw ERR_NEEDMOREPARAMS if there are less than 4 arguments")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peermanager, channels};

		message.argCount = 0;
		REQUIRE_THROWS_AS( command_user(message, deps), ERR_NEEDMOREPARAMS );
		message.arguments[0] = "hello";
		message.argCount = 3;
		REQUIRE_THROWS_AS( command_user(message, deps), ERR_NEEDMOREPARAMS );
	};
	SECTION("should throw ERR_ALREADYREGISTERED")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peermanager, channels};

		message.argCount = 4;
		message.peer._registered = true;
		REQUIRE_THROWS_AS( command_user(message, deps), ERR_ALREADYREGISTRED );
	};
	SECTION("should ignore the command")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peermanager, channels};

		message.argCount = 4;
		message.arguments[0] = "te@st";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "john doe";
		message.peer._username = "user";
		command_user(message, deps);
		REQUIRE( message.peer._username == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te\rst";
		message.peer._username = "user";
		command_user(message, deps);
		REQUIRE( message.peer._username == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te\nst";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "john doe";
		message.peer._username = "user";
		command_user(message, deps);
		REQUIRE( message.peer._username == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te0st";
		message.arguments[0][2] = '\0';
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "john doe";
		message.peer._username = "user";
		command_user(message, deps);
		REQUIRE( message.peer._username == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te st";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "john doe";
		message.peer._username = "user";
		command_user(message, deps);
		REQUIRE( message.peer._username == "user" );
	};
	SECTION("should correctly parse the arguments")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peermanager, channels};

		peer._nickname = "ppik";
		message.argCount = 4;
		message.arguments[0] = "user";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "john doe";
		command_user(message, deps);
		REQUIRE( message.peer._username == "user" );
		REQUIRE( message.peer._realname == "john doe" );
		REQUIRE( message.peer._registered == true );
	};
	SECTION("should closeConnection if the password is wrong")
	{
		struct sockaddr	addr;
		Configuration	config;
		config._password = "test";
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		&peermanager = server.peers;
		ChannelManager	channels;
		Dependencies	deps = {config, peermanager, channels};

		peer._nickname = "ppik";
		message.argCount = 4;
		message.arguments[0] = "user";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "john doe";
		peermanager.add(3, addr);
		peer._password = "wrong";
		REQUIRE( command_user(message, deps) == 0 );
	};
	SECTION("should register if the peer has all fields")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		peer._nickname = "ppik";
		message.argCount = 4;
		message.arguments[0] = "user";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "ppiques";
		command_user(message, deps);
		REQUIRE( peer.isRegistered() );
	};
	SECTION("should register if the peer has all fields")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		peer._nickname = "ppik";
		message.argCount = 4;
		message.arguments[0] = "user";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "ppiques";
		command_user(message, deps);
		REQUIRE( peer.isRegistered() );
	};
};
