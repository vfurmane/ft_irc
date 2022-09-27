#include <cstring>
#include "catch.hpp"

#define private public
#include "Message.hpp"

TEST_CASE("Message::parse()")
{
	SECTION("Should parse full message correctly")
	{
		Message IM(":prefix command arg0 arg1\r\n");
		IM.parse();
		REQUIRE( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE( IM.command.compare("command") == 0 );
		REQUIRE( IM.arguments[0].compare("arg0") == 0 );
		REQUIRE( IM.arguments[1].compare("arg1") == 0 );
		REQUIRE( IM.argCount == 2 );
	}
	SECTION("Should parse messages with missing arguments")
	{
		Message IM(":prefix command\r\n");
		IM.parse();
		REQUIRE( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE( IM.command.compare("command") == 0 );
		REQUIRE( IM.argCount == 0 );
	}
	SECTION("Should parse messages with no prefix")
	{
		Message IM("command arg0\r\n");
		IM.parse();
		REQUIRE( IM.command.compare("command") == 0 );
		REQUIRE( IM.arguments[0].compare("arg0") == 0 );
		REQUIRE( IM.argCount == 1 );
	}
	SECTION("Should parse messages containing only a command")
	{
		Message IM("command\r\n");
		IM.parse();
		REQUIRE( IM.command.compare("command") == 0 );
	}
	SECTION("Should parse correctly up to 15 arguments")
	{
		Message IM("command 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\r\n");
		IM.parse();
		REQUIRE ( IM.command.compare("command") == 0 );
		REQUIRE ( IM.arguments[0].compare("0") == 0 );
		REQUIRE ( IM.arguments[14].compare("14") == 0 );
		REQUIRE( IM.argCount == 15 );
	}
	SECTION("Should parse prefix and not crash")
	{
		Message IM(":prefix\r\n");
		IM.parse();
		REQUIRE ( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM.command.compare("") == 0 );
		REQUIRE ( IM.arguments[0].compare("") == 0 );
		REQUIRE ( IM.argCount == 0 );
	}
	SECTION("Should parse correctly a single trailingArg argument")
	{
		Message IM(":prefix  :arg0 arg1\r\n");
		IM.parse();
		REQUIRE ( IM.prefix[0].compare("prefix") == 0 );
		REQUIRE ( IM.command.compare("") == 0 );
		REQUIRE ( IM.arguments[0].compare("arg0 arg1") == 0);
		REQUIRE ( IM.argCount == 1 );
	}
	SECTION("Should parse correctly multiple args with a trailingArg")
	{	
		Message IM(": command arg0 arg1 :arg2 arg3\r\n");
		IM.parse();
		REQUIRE ( IM.prefix[0].compare("") == 0 );
		REQUIRE ( IM.command.compare("command") == 0 );
		REQUIRE ( IM.arguments[0].compare("arg0") == 0);
		REQUIRE ( IM.arguments[1].compare("arg1") == 0);
		REQUIRE ( IM.arguments[2].compare("arg2 arg3") == 0);
		REQUIRE ( IM.argCount == 3 );
	}
}
