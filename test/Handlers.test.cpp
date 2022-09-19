#include <cstring>
#include "catch.hpp"

#define private public
#include "handlers.hpp"

TEST_CASE("IRC::lexer()")
{
	SECTION("Should parse message correctly")
	{
		struct inputLexer test1 = lexer(":prefix command arg0 arg1\r\n");

		REQUIRE( test1.prefix[0].compare("prefix") == 0 );
		REQUIRE( test1.command.compare("command") == 0 );
		REQUIRE( test1.arguments[0].compare("arg0") == 0 );
		REQUIRE( test1.arguments[1].compare("arg1") == 0 );
	}
}

