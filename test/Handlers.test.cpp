#include <cstring>
#include "catch.hpp"

#define private public
#include "handlers.hpp"

TEST_CASE("IRC::lexer()")
{
	SECTION("Should parse full message correctly")
	{
		struct inputLexer test1 = lexer(":prefix command arg0 arg1\r\n");
		REQUIRE( test1.prefix[0].compare("prefix") == 0 );
		REQUIRE( test1.command.compare("command") == 0 );
		REQUIRE( test1.arguments[0].compare("arg0") == 0 );
		REQUIRE( test1.arguments[1].compare("arg1") == 0 );
	}
	SECTION("Should parse messages with missing arguments or prefix correctly")
	{
		struct inputLexer test2 = lexer(":prefix command\r\n");
		REQUIRE( test2.prefix[0].compare("prefix") == 0 );
		REQUIRE( test2.command.compare("command") == 0 );
		
		struct inputLexer test3 = lexer("command arg0\r\n");
		REQUIRE( test3.command.compare("command") == 0 );
		REQUIRE( test3.arguments[0].compare("arg0") == 0 );

		struct inputLexer test4 = lexer("command\r\n");
		REQUIRE( test4.command.compare("command") == 0 );
	
		struct inputLexer test5 = lexer("command 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\r\n");
		REQUIRE ( test5.command.compare("command") == 0 );
		REQUIRE ( test5.arguments[0].compare("0") == 0 );
		REQUIRE ( test5.arguments[14].compare("14") == 0 );	
	}
	SECTION("Should parse prefix and not crash")
	{
		struct inputLexer test6 = lexer(":prefix\r\n");
		REQUIRE ( test6.prefix[0].compare("prefix") == 0 );
		REQUIRE ( test6.command.compare("") == 0 );
		REQUIRE ( test6.arguments[0].compare("") == 0 );
	}
}

