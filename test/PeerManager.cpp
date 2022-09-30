#include "catch.hpp"
#include "mocks.hpp"

#include "../src/PeerManager.cpp"

TEST_CASE("areSameNickname")
{
	SECTION("when the nickname are the same")
	{
		REQUIRE( areSameNickname("john-doe", "john-doe") );
		REQUIRE( areSameNickname("j^hn-d0e", "j^hn-d0e") );
		REQUIRE( areSameNickname("j^hn-doe", "j~hn-doe") );
		REQUIRE( areSameNickname("ja[d}e", "ja[d}e") );
		REQUIRE( areSameNickname("John-doe", "john-Doe") );
		REQUIRE( areSameNickname("ja{d]e", "ja[d}e") );
	};
	SECTION("when the nickname are not the same")
	{
		REQUIRE( !areSameNickname("john-doe", "jade-doe") );
		REQUIRE( !areSameNickname("j0hn-doe", "john-doe") );
		REQUIRE( !areSameNickname("ja[d}e", "ja}d[e") );
	};
};
