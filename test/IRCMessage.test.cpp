#include <cstring>
#include "catch.hpp"

#define private public
#define protected public
#include "IRCMessage.hpp"
#include "IRCPeer.hpp"

TEST_CASE("IRCMessage::parse()")
{
	SECTION("Should parse full message correctly")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, ":prefix command arg0 arg1\r\n");
		IM.parse();
		REQUIRE( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE( IM._command.compare("command") == 0 );
		REQUIRE( IM._arguments[0].compare("arg0") == 0 );
		REQUIRE( IM._arguments[1].compare("arg1") == 0 );
		REQUIRE( IM._argCount == 2 );
	}
	SECTION("Should parse messages with missing arguments")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, ":prefix command\r\n");
		IM.parse();
		REQUIRE( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE( IM._command.compare("command") == 0 );
		REQUIRE( IM._argCount == 0 );
	}
	SECTION("Should parse messages with no prefix")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, "command arg0\r\n");
		IM.parse();
		REQUIRE( IM._command.compare("command") == 0 );
		REQUIRE( IM._arguments[0].compare("arg0") == 0 );
		REQUIRE( IM._argCount == 1 );
	}
	SECTION("Should parse messages containing only a command")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, "command\r\n");
		IM.parse();
		REQUIRE( IM._command.compare("command") == 0 );
	}
	SECTION("Should parse correctly up to 15 arguments")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, "command 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\r\n");
		IM.parse();
		REQUIRE ( IM._command.compare("command") == 0 );
		REQUIRE ( IM._arguments[0].compare("0") == 0 );
		REQUIRE ( IM._arguments[14].compare("14") == 0 );
		REQUIRE( IM._argCount == 15 );
	}
	SECTION("Should parse prefix and not crash")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, ":prefix\r\n");
		IM.parse();
		REQUIRE ( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM._command.compare("") == 0 );
		REQUIRE ( IM._arguments[0].compare("") == 0 );
		REQUIRE ( IM._argCount == 0 );
	}
	SECTION("Should parse correctly a single trailingArg argument")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, ":prefix  :arg0 arg1\r\n");
		IM.parse();
		REQUIRE ( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM._command.compare("") == 0 );
		REQUIRE ( IM._arguments[0].compare("arg0 arg1") == 0);
		REQUIRE ( IM._argCount == 1 );
	}
	SECTION("Should parse correctly multiple args with a trailingArg")
	{	
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, ": command arg0 arg1 :arg2 arg3\r\n");
		IM.parse();
		REQUIRE ( IM._prefix[0].compare("") == 0 );
		REQUIRE ( IM._command.compare("command") == 0 );
		REQUIRE ( IM._arguments[0].compare("arg0") == 0);
		REQUIRE ( IM._arguments[1].compare("arg1") == 0);
		REQUIRE ( IM._arguments[2].compare("arg2 arg3") == 0);
		REQUIRE ( IM._argCount == 3 );
	}
}

TEST_CASE("IRCMessage::_updateInputFromFields")
{
	SECTION("Should ignore prefix if it is NULL")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, std::string());
		IM._command = "COMMAND";
		IM._updateInputFromFields();
		REQUIRE( IM._input == "COMMAND" );
	};
	SECTION("Should include prefix if it is not NULL")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, std::string());
		IM._prefix = new std::string("prefix");
		IM._command = "COMMAND";
		IM._updateInputFromFields();
		REQUIRE( IM._input == ":prefix COMMAND" );
	};
	SECTION("Should include all arguments")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, std::string());
		IM._command = "COMMAND";
		IM._arguments[0] = "arg1";
		IM._arguments[1] = "arg2";
		IM._argCount = 2;
		IM._updateInputFromFields();
		REQUIRE( IM._input == "COMMAND arg1 arg2" );
	};
	SECTION("Should include all arguments with trailing")
	{
		struct sockaddr	addr;
		IRCPeer	peer(3, addr);
		IRCMessage IM(peer, std::string());
		IM._command = "COMMAND";
		IM._arguments[0] = "arg1";
		IM._arguments[1] = "arg2";
		IM._arguments[2] = "arg3 and arg4";
		IM._argCount = 3;
		IM._updateInputFromFields();
		REQUIRE( IM._input == "COMMAND arg1 arg2 :arg3 and arg4" );
	};
};
