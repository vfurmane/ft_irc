#include <cstring>
#include "catch.hpp"

#define private public
#include "IRCMessage.hpp"

TEST_CASE("IRCMessage::parse()")
{
	SECTION("Should parse full message correctly")
	{
		IRCMessage IM(":prefix command arg0 arg1\r\n");
		IM.parse();
		REQUIRE( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE( IM._command.compare("command") == 0 );
		REQUIRE( IM._arguments[0].compare("arg0") == 0 );
		REQUIRE( IM._arguments[1].compare("arg1") == 0 );
		REQUIRE( IM._argCount == 2 );
	}
	SECTION("Should parse messages with missing arguments")
	{
		IRCMessage IM(":prefix command\r\n");
		IM.parse();
		REQUIRE( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE( IM._command.compare("command") == 0 );
		REQUIRE( IM._argCount == 0 );
	}
	SECTION("Should parse messages with no prefix")
	{
		IRCMessage IM("command arg0\r\n");
		IM.parse();
		REQUIRE( IM._command.compare("command") == 0 );
		REQUIRE( IM._arguments[0].compare("arg0") == 0 );
		REQUIRE( IM._argCount == 1 );
	}
	SECTION("Should parse messages containing only a command")
	{
		IRCMessage IM("command\r\n");
		IM.parse();
		REQUIRE( IM._command.compare("command") == 0 );
	}
	SECTION("Should parse correctly up to 15 arguments")
	{
		IRCMessage IM("command 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\r\n");
		IM.parse();
		REQUIRE ( IM._command.compare("command") == 0 );
		REQUIRE ( IM._arguments[0].compare("0") == 0 );
		REQUIRE ( IM._arguments[14].compare("14") == 0 );
		REQUIRE( IM._argCount == 15 );
	}
	SECTION("Should parse prefix and not crash")
	{
		IRCMessage IM(":prefix\r\n");
		IM.parse();
		REQUIRE ( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM._command.compare("") == 0 );
		REQUIRE ( IM._arguments[0].compare("") == 0 );
		REQUIRE ( IM._argCount == 0 );
	}
	SECTION("Should parse correctly a single trailingArg argument")
	{
		IRCMessage IM(":prefix  :arg0 arg1\r\n");
		IM.parse();
		REQUIRE ( IM._prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM._command.compare("") == 0 );
		REQUIRE ( IM._arguments[0].compare("arg0 arg1") == 0);
		REQUIRE ( IM._argCount == 1 );
	}
	SECTION("Should parse correctly multiple args with a trailingArg")
	{	
		IRCMessage IM(": command arg0 arg1 :arg2 arg3\r\n");
		IM.parse();
		REQUIRE ( IM._prefix[0].compare("") == 0 );
		REQUIRE ( IM._command.compare("command") == 0 );
		REQUIRE ( IM._arguments[0].compare("arg0") == 0);
		REQUIRE ( IM._arguments[1].compare("arg1") == 0);
		REQUIRE ( IM._arguments[2].compare("arg2 arg3") == 0);
		REQUIRE ( IM._argCount == 3 );
	}
}
