#include <cstring>
#include "catch.hpp"

#define private public
#include "IRCMessageStream.hpp"

TEST_CASE("IRCMessageStream::parse()")
{
	SECTION("Should parse full message correctly")
	{
		IRCMessageStream IMS(":prefix command arg0 arg1\r\n");
		IMS.parse();
		REQUIRE( IMS._prefix[0].compare("prefix") == 0 );
		REQUIRE( IMS._command.compare("command") == 0 );
		REQUIRE( IMS._arguments[0].compare("arg0") == 0 );
		REQUIRE( IMS._arguments[1].compare("arg1") == 0 );
		REQUIRE( IMS._argCount == 2 );
	}
	SECTION("Should parse messages with missing arguments")
	{
		IRCMessageStream IMS(":prefix command\r\n");
		IMS.parse();
		REQUIRE( IMS._prefix[0].compare("prefix") == 0 );
		REQUIRE( IMS._command.compare("command") == 0 );
		REQUIRE( IMS._argCount == 0 );
	}
	SECTION("Should parse messages with no prefix")
	{
		IRCMessageStream IMS("command arg0\r\n");
		IMS.parse();
		REQUIRE( IMS._command.compare("command") == 0 );
		REQUIRE( IMS._arguments[0].compare("arg0") == 0 );
		REQUIRE( IMS._argCount == 1 );
	}
	SECTION("Should parse messages containing only a command")
	{
		IRCMessageStream IMS("command\r\n");
		IMS.parse();
		REQUIRE( IMS._command.compare("command") == 0 );
	}
	SECTION("Should parse correctly up to 15 arguments")
	{
		IRCMessageStream IMS("command 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\r\n");
		IMS.parse();
		REQUIRE ( IMS._command.compare("command") == 0 );
		REQUIRE ( IMS._arguments[0].compare("0") == 0 );
		REQUIRE ( IMS._arguments[14].compare("14") == 0 );
		REQUIRE( IMS._argCount == 15 );
	}
	SECTION("Should parse prefix and not crash")
	{
		IRCMessageStream IMS(":prefix\r\n");
		IMS.parse();
		REQUIRE ( IMS._prefix[0].compare("prefix") == 0 );
		REQUIRE ( IMS._command.compare("") == 0 );
		REQUIRE ( IMS._arguments[0].compare("") == 0 );
		REQUIRE ( IMS._argCount == 0 );
	}
	SECTION("Should parse correctly a single trailingArg argument")
	{
		IRCMessageStream IMS(":prefix  :arg0 arg1\r\n");
		IMS.parse();
		REQUIRE ( IMS._prefix[0].compare("prefix") == 0 );
		REQUIRE ( IMS._command.compare("") == 0 );
		REQUIRE ( IMS._arguments[0].compare("arg0 arg1") == 0);
		REQUIRE ( IMS._argCount == 1 );
	}
	SECTION("Should parse correctly multiple args with a trailingArg")
	{	
		IRCMessageStream IMS(": command arg0 arg1 :arg2 arg3\r\n");
		IMS.parse();
		REQUIRE ( IMS._prefix[0].compare("") == 0 );
		REQUIRE ( IMS._command.compare("command") == 0 );
		REQUIRE ( IMS._arguments[0].compare("arg0") == 0);
		REQUIRE ( IMS._arguments[1].compare("arg1") == 0);
		REQUIRE ( IMS._arguments[2].compare("arg2 arg3") == 0);
		REQUIRE ( IMS._argCount == 3 );
	}
}
