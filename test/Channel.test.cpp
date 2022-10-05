#include <sstream>
#include "catch.hpp"

#define private public
#include "../src/Channel.cpp"

TEST_CASE("Channel::setKey")
{
	SECTION("should save the key")
	{
		Channel	channel("general");

		channel.setKey("key");
		REQUIRE( channel._key == "key" );
	};
};

TEST_CASE("Channel::unsetKey")
{
	SECTION("should change the key")
	{
		Channel	channel("general");

		channel._key = "key";
		channel.unsetKey();
		REQUIRE( channel._key.empty() );
	};
};

TEST_CASE("Channel::setKey and Channel::unsetKey")
{
	SECTION("should change the key")
	{
		Channel	channel("general");

		channel.setKey("key");
		channel.unsetKey();
		channel.setKey("password");
		REQUIRE( channel._key == "password" );
	};
};

TEST_CASE("Channel::compareKey")
{
	SECTION("should validate the key")
	{
		Channel	channel("general");

		channel._key = "key";
		REQUIRE( channel.compareKey("key") );
	};
	SECTION("should not validate the key")
	{
		Channel	channel("general");

		channel._key = "key";
		REQUIRE( !channel.compareKey("password") );
	};
};
