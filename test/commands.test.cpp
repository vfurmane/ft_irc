#include <sstream>
#include "catch.hpp"

#define protected public
#include "../src/commands.cpp"

TEST_CASE("parseChannel")
{
	SECTION("with a '#' prefix")
	{
		_base_channel ret = parseChannel("#hello");
		REQUIRE( ret._name == "hello" );
		REQUIRE( ret._namespace == PUBLIC );
	};
	SECTION("with a length of 50 character")
	{
		REQUIRE_NOTHROW( parseChannel("#thisisaquitelongchannelnameequaltofiftycharacters") );
	};
	SECTION("with a length greater than 50 characters")
	{
		REQUIRE_THROWS_AS( parseChannel("#thisisaverylongchannelnamelongerthanfiftycharacters"), InvalidChannelName );
	};
};

TEST_CASE("parseList")
{
	std::vector<std::string>	ret;

	SECTION("with a single-element list")
	{
		ret = parseList("hello");
		REQUIRE( ret[0] == "hello" );
		REQUIRE( ret.size() == 1 );

		ret = parseList("element1");
		REQUIRE( ret[0] == "element1" );
		REQUIRE( ret.size() == 1 );
	};
	SECTION("with a very basic list")
	{
		ret = parseList("hello,world");
		REQUIRE( ret[0] == "hello" );
		REQUIRE( ret[1] == "world" );
		REQUIRE( ret.size() == 2 );

		ret = parseList("element1,element2,element3");
		REQUIRE( ret[0] == "element1" );
		REQUIRE( ret[1] == "element2" );
		REQUIRE( ret[2] == "element3" );
		REQUIRE( ret.size() == 3 );
	};
	SECTION("with an empty list")
	{
		REQUIRE_THROWS_AS( parseList(""), std::out_of_range );
	};
	SECTION("with a list that ends with a separator")
	{
		ret = parseList("hello,");
		REQUIRE( ret[0] == "hello" );
		REQUIRE( ret[1] == "" );
		REQUIRE( ret.size() == 2 );

		ret = parseList("element1,element2,element3,");
		REQUIRE( ret[0] == "element1" );
		REQUIRE( ret[1] == "element2" );
		REQUIRE( ret[2] == "element3" );
		REQUIRE( ret[3] == "" );
		REQUIRE( ret.size() == 4 );
	};
	SECTION("with consecutive separators")
	{
		ret = parseList("hello,,world");
		REQUIRE( ret[0] == "hello" );
		REQUIRE( ret[1] == "" );
		REQUIRE( ret[2] == "world" );
		REQUIRE( ret.size() == 3 );

		ret = parseList("element1,element2,,element3");
		REQUIRE( ret[0] == "element1" );
		REQUIRE( ret[1] == "element2" );
		REQUIRE( ret[2] == "" );
		REQUIRE( ret[3] == "element3" );
		REQUIRE( ret.size() == 4 );

		ret = parseList("hello,,");
		REQUIRE( ret[0] == "hello" );
		REQUIRE( ret[1] == "" );
		REQUIRE( ret[2] == "" );
		REQUIRE( ret.size() == 3 );
	};
};
