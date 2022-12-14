#include "catch.hpp"
#include "mocks.hpp"
#include <sstream>
#include <vector>

#define private public
#define protected public
#include "commands.hpp"
#include "IRCErrors.hpp"
#include "Message.hpp"
#include "Peer.hpp"

#include "../src/commands/nick.cpp"

bool	isValidNickname(const std::string &nick);

TEST_CASE("isValidNickname")
{
	SECTION("when nick is empty")
	{
		REQUIRE( !isValidNickname("") );
	};
	SECTION("when nick is too long")
	{
		REQUIRE( !isValidNickname("johndoe123456") );
	};
	SECTION("when nick starts with a digit")
	{
		REQUIRE( !isValidNickname("123john") );
		REQUIRE( !isValidNickname("672jade") );
	};
	SECTION("when nick starts with a forbidden character")
	{
		REQUIRE( !isValidNickname("-john") );
		REQUIRE( !isValidNickname("#john") );
		REQUIRE( !isValidNickname("@john") );
	};
	SECTION("when nick contains a forbidden character")
	{
		REQUIRE( !isValidNickname("john#") );
		REQUIRE( !isValidNickname("j@de") );
	};
	SECTION("when nick contains multiple forbidden characters")
	{
		REQUIRE( !isValidNickname("j%hn#") );
		REQUIRE( !isValidNickname("j@de@hi") );
	};
	SECTION("when nick is valid")
	{
		REQUIRE( isValidNickname("john-doe1") );
		REQUIRE( isValidNickname("j4de") );
		REQUIRE( isValidNickname("[john]") );
		REQUIRE( isValidNickname("[{jade}]") );
		REQUIRE( isValidNickname("[{-}]") );
		REQUIRE( isValidNickname("[0-1]") );
	};
};

TEST_CASE("NICK")
{
	g_send_arg_sockfd.clear();

	SECTION("should throw ERR_NONICKNAMEGIVEN if the no nickname was given")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		message.argCount = 0;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_NONICKNAMEGIVEN );
		message.arguments[0] = "";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_NONICKNAMEGIVEN );
	};
	SECTION("should throw ERR_ERRONEUSNICKNAME if the nicname is erroneous")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		message.arguments[0] = "j@de@hi";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_ERRONEUSNICKNAME );
		message.arguments[0] = "123john";
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_ERRONEUSNICKNAME );
	};
	SECTION("should throw ERR_NICKNAMEINUSE if the nickname is in use")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		message.arguments[0] = "j@de@hi";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_ERRONEUSNICKNAME );
		message.arguments[0] = "123john";
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_ERRONEUSNICKNAME );
	};
	SECTION("should throw ERR_NICKNAMEINUSE if the nickname is in use")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		message.arguments[0] = "j@de@hi";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_ERRONEUSNICKNAME );
		message.arguments[0] = "123john";
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_ERRONEUSNICKNAME );
	};
	SECTION("should throw ERR_NICKNAMEINUSE if the nickname is in use")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		peers.add(3, addr);
		peers.get(3).setNickname("john");
		message.arguments[0] = "john";
		message.argCount = 1;
		REQUIRE_THROWS_AS( command_nick(message, deps), ERR_NICKNAMEINUSE );
	};
	SECTION("should set the nickname of the user")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(server, 3, addr);
		Message			message(peer, std::string());
		PeerManager		peers(server);
		ChannelManager	channels;
		Dependencies	deps = {config, peers, channels};

		message.arguments[0] = "nickname";
		message.argCount = 1;
		command_nick(message, deps);
		REQUIRE( peer._nickname == "nickname" );
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

		peer._username = "username";
		peer._realname = "Real Name";
		message.arguments[0] = "nickname";
		message.argCount = 1;
		command_nick(message, deps);
		REQUIRE( peer.isRegistered() );
	};
};
