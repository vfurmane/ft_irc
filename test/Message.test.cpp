#include <cstring>
#include <sstream>
#include "catch.hpp"
#include "mocks.hpp"

#define private public
#include "Message.hpp"

#include "../src/Message.cpp"

TEST_CASE("Message::parse()")
{
	SECTION("Should parse full message correctly")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer			peer(server, 3, address);
		Message			IM(peer, ":prefix command arg0 arg1\r\n");
		IM.parse();
		REQUIRE( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE( IM.command.compare("command") == 0 );
		REQUIRE( IM.arguments[0].compare("arg0") == 0 );
		REQUIRE( IM.arguments[1].compare("arg1") == 0 );
		REQUIRE( IM.argCount == 2 );
	}
	SECTION("Should parse messages with missing arguments")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer	peer(server, 3, address);
		Message IM(peer, ":prefix command\r\n");
		IM.parse();
		REQUIRE( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE( IM.command.compare("command") == 0 );
		REQUIRE( IM.argCount == 0 );
	}
	SECTION("Should parse messages with no prefix")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer	peer(server, 3, address);
		Message IM(peer, "command arg0\r\n");
		IM.parse();
		REQUIRE( IM.command.compare("command") == 0 );
		REQUIRE( IM.arguments[0].compare("arg0") == 0 );
		REQUIRE( IM.argCount == 1 );
	}
	SECTION("Should parse messages containing only a command")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer	peer(server, 3, address);
		Message IM(peer, "command\r\n");
		IM.parse();
		REQUIRE( IM.command.compare("command") == 0 );
	}
	SECTION("Should parse correctly up to 15 arguments")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer	peer(server, 3, address);
		Message IM(peer, "command 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\r\n");
		IM.parse();
		REQUIRE ( IM.command.compare("command") == 0 );
		REQUIRE ( IM.arguments[0].compare("0") == 0 );
		REQUIRE ( IM.arguments[14].compare("14") == 0 );
		REQUIRE( IM.argCount == 15 );
	}
	SECTION("Should parse prefix and not crash")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer	peer(server, 3, address);
		Message IM(peer, ":prefix\r\n");
		IM.parse();
		REQUIRE ( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM.command.compare("") == 0 );
		REQUIRE ( IM.arguments[0].compare("") == 0 );
		REQUIRE ( IM.argCount == 0 );
	}
	SECTION("Should parse correctly a single trailingArg argument")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer	peer(server, 3, address);
		Message IM(peer, ":prefix  :arg0 arg1\r\n");
		IM.parse();
		REQUIRE ( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM.command.compare("") == 0 );
		REQUIRE ( IM.arguments[0].compare("arg0 arg1") == 0);
		REQUIRE ( IM.argCount == 1 );
	}
	SECTION("Should parse correctly multiple args with a trailingArg")
	{	
		Configuration	config;
		Server			server(config);
		struct sockaddr	address;
		Peer	peer(server, 3, address);
		Message IM(peer, ": command arg0 arg1 :arg2 arg3\r\n");
		IM.parse();
		REQUIRE ( IM.prefix[0].compare("") == 0 );
		REQUIRE ( IM.command.compare("command") == 0 );
		REQUIRE ( IM.arguments[0].compare("arg0") == 0);
		REQUIRE ( IM.arguments[1].compare("arg1") == 0);
		REQUIRE ( IM.arguments[2].compare("arg2 arg3") == 0);
		REQUIRE ( IM.argCount == 3 );
	}
	SECTION("Should set the prefix without registration")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr address;
		Peer	peer(server, 3, address);
		peer.setNickname("nickTest");	
		Message IM(peer, "command arg0");
		IM.updatePrefixFromPeer();

		std::string prefixReference = "nickTest@";
		prefixReference += peer.getStrAddr();
		REQUIRE(IM.prefix[0] == prefixReference);
	}
	SECTION("Should set the prefix with registration")
	{
		Configuration	config;
		Server			server(config);
		struct sockaddr address;
		Peer	peer(server, 3, address);
		peer._username = "testUser";
		peer._realname = "Real Name";
		peer.setNickname("nickTest");	
		peer.registration();
		Message IM(peer, "command arg0");
		IM.updatePrefixFromPeer();

		std::string prefixReference = "nickTest!testUser@";
		prefixReference += peer.getStrAddr();
		REQUIRE(IM.prefix[0] == prefixReference);
	}
}
