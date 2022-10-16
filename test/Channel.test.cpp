#include <sstream>
#include "catch.hpp"

#define private public
#define protected public
#include "../src/Channel.cpp"

TEST_CASE("_base_channel::parse")
{
	SECTION("with a '#' prefix")
	{
		_base_channel ret = _base_channel::parse("#hello");
		REQUIRE( ret._name == "hello" );
		REQUIRE( ret._namespace == PUBLIC );
	};
	SECTION("with a length of 50 character")
	{
		REQUIRE_NOTHROW( _base_channel::parse("#thisisaquitelongchannelnameequaltofiftycharacters") );
	};
	SECTION("with a length greater than 50 characters")
	{
		REQUIRE_THROWS_AS( _base_channel::parse("#thisisaverylongchannelnamelongerthanfiftycharacters"), InvalidChannelName );
	};
};

TEST_CASE("_base_channel::stringify")
{
	SECTION("with a public namespace")
	{
		_base_channel	channel("general");

		REQUIRE( channel.stringify() == "#general" );
	};
};

TEST_CASE("Channel::setKey")
{
	SECTION("should save the key")
	{
		ChannelManager	channels;
		Channel			channel(channels, "general");

		channel.setKey("key");
		REQUIRE( channel._key == "key" );
	};
};

TEST_CASE("Channel::unsetKey")
{
	SECTION("should change the key")
	{
		ChannelManager	channels;
		Channel			channel(channels, "general");

		channel._key = "key";
		channel.unsetKey();
		REQUIRE( channel._key.empty() );
	};
};

TEST_CASE("Channel::setKey and Channel::unsetKey")
{
	SECTION("should change the key")
	{
		ChannelManager	channels;
		Channel			channel(channels, "general");

		channel.setKey("key");
		channel.unsetKey();
		channel.setKey("password");
		REQUIRE( channel._key == "password" );
	};
};

TEST_CASE("Channel::compareKey")
{
	SECTION("should ignore if the key is empty")
	{
		ChannelManager	channels;
		Channel			channel(channels, "general");

		channel._key = "";
		REQUIRE( channel.compareKey("") );
		REQUIRE( channel.compareKey("key") );
	};
	SECTION("should validate the key")
	{
		ChannelManager	channels;
		Channel			channel(channels, "general");

		channel._key = "key";
		REQUIRE( channel.compareKey("key") );
	};
	SECTION("should not validate the key")
	{
		ChannelManager	channels;
		Channel			channel(channels, "general");

		channel._key = "key";
		REQUIRE( !channel.compareKey("password") );
	};
};
