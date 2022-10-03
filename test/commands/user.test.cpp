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
		Peer			peer(3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		Dependencies	deps = {config, peermanager};

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
		Peer			peer(3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		Dependencies	deps = {config, peermanager};

		message.argCount = 4;
		message.peer._registered = true;
		REQUIRE_THROWS_AS( command_user(message, deps), ERR_ALREADYREGISTRED );
	};
	SECTION("should ignore the command")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		Dependencies	deps = {config, peermanager};

		message.argCount = 4;
		message.arguments[0] = "te@st";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "ppiques";
		message.peer._user = "user";
		command_user(message, deps);
		REQUIRE( message.peer._user == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te\rst";
		message.peer._user = "user";
		command_user(message, deps);
		REQUIRE( message.peer._user == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te\nst";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "ppiques";
		message.peer._user = "user";
		command_user(message, deps);
		REQUIRE( message.peer._user == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te0st";
		message.arguments[0][2] = '\0';
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "ppiques";
		message.peer._user = "user";
		command_user(message, deps);
		REQUIRE( message.peer._user == "user" );

		message.peer._registered = false;
		message.arguments[0] = "te st";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "ppiques";
		message.peer._user = "user";
		command_user(message, deps);
		REQUIRE( message.peer._user == "user" );
	};
	SECTION("should correctly parse the arguments")
	{
		struct sockaddr	addr;
		Configuration	config;
		Server			server(config);
		Peer			peer(3, addr);
		Message			message(peer, std::string());
		PeerManager		peermanager(server);
		Dependencies	deps = {config, peermanager};

		message.argCount = 4;
		message.arguments[0] = "user";
		message.arguments[1] = "0";
		message.arguments[2] = "*";
		message.arguments[3] = "ppiques";
		command_user(message, deps);
		REQUIRE( message.peer._user == "user" );
		REQUIRE( message.peer._mode == "0" );
		REQUIRE( message.peer._realname == "ppiques" );
		REQUIRE( message.peer._registered == true );
	};
};
