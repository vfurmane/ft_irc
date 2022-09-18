#include <cstring>
#include "catch.hpp"

#define private public
#include "Configuration.hpp"

TEST_CASE("parse_port_number")
{
	SECTION("should work")
	{
		REQUIRE( Configuration::parse_port_number("1") == 1 );
		REQUIRE( Configuration::parse_port_number("42") == 42 );
		REQUIRE( Configuration::parse_port_number("443") == 443 );
		REQUIRE( Configuration::parse_port_number("3000") == 3000 );
		REQUIRE( Configuration::parse_port_number("65535") == 65535 );
		REQUIRE( Configuration::parse_port_number("008080") == 8080 );
	}
	SECTION("should not work")
	{
		REQUIRE_THROWS_AS( Configuration::parse_port_number("0"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("-15"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("00-15"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("-0015"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("+15"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("22a"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("a22"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("2a2"), Configuration::NotAPortNumber );
		REQUIRE_THROWS_AS( Configuration::parse_port_number("65536"), Configuration::NotAPortNumber );
	}
}

TEST_CASE("Configuration::parse_arguments()")
{
	SECTION("should provide three arguments")
	{
		Configuration	conf;

		REQUIRE_THROWS_AS( conf.parse_arguments(1, NULL), Configuration::NotEnoughArguments );
		REQUIRE_THROWS_AS( conf.parse_arguments(2, NULL), Configuration::NotEnoughArguments );
		REQUIRE_THROWS_AS( conf.parse_arguments(4, NULL), Configuration::NotEnoughArguments );
	}

	SECTION("cannot parse again")
	{
		Configuration	conf;

		conf._parsed = true;
		REQUIRE_THROWS_AS( conf.parse_arguments(2, NULL), Configuration::AlreadyParsed );
	}

	SECTION("parsing the port")
	{
		Configuration	conf;
		char			argv1[] = "ircserv";
		char			argv2[] = "6667";
		char			argv3[] = "password";
		char			*argv[3] = {argv1, argv2, argv3};

		conf.parse_arguments(3, argv);

		REQUIRE( conf.getPort() == 6667 );
		REQUIRE( strcmp(conf.getStrPort(), "6667") == 0 );
	}
}
