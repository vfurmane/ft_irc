#include "catch.hpp"

#include "../include/Manager.hpp"

typedef Manager<int, double> TestManager;

TEST_CASE("Manager")
{
	TestManager	micheal; // pronounced /ˈmænɪgɚ /

	SECTION("copy constructor")
	{
		micheal.add(0, 3.1415);

		TestManager	charles(micheal);
		REQUIRE( charles[0] == 3.1415 );
	};
	SECTION("assignation operator")
	{
		micheal.add(0, 3.1415);

		TestManager	charles = micheal;
		REQUIRE( charles[0] == 3.1415 );
	};
	SECTION("array subscript operator")
	{
		micheal.add(0, 3.1415);

		REQUIRE( micheal[0] == 3.1415 );
	};
	SECTION("begin and end")
	{
		micheal.add(0, 3.1415);
		micheal.add(1, 2.7182);

		TestManager::iterator it1 = micheal.begin();
		TestManager::iterator it2 = (++micheal.begin());
		REQUIRE( it1->second == 3.1415 );
		REQUIRE( it2->second == 2.7182 );

		it1 = (--micheal.end());
		it2 = (--(--micheal.end()));
		REQUIRE( it1->second == 2.7182 );
		REQUIRE( it2->second == 3.1415 );
	};
	SECTION("const begin and end")
	{
		micheal.add(0, 3.1415);
		micheal.add(1, 2.7182);

		TestManager::const_iterator it1 = micheal.begin();
		TestManager::const_iterator it2 = (++micheal.begin());
		REQUIRE( it1->second == 3.1415 );
		REQUIRE( it2->second == 2.7182 );

		it1 = (--micheal.end());
		it2 = (--(--micheal.end()));
		REQUIRE( it1->second == 2.7182 );
		REQUIRE( it2->second == 3.1415 );
	};
	SECTION("clear")
	{
		micheal.add(0, 3.1415);
		micheal.clear();
		REQUIRE( !micheal.has(0) );
	};
	SECTION("add")
	{
		micheal.add(0, 3.1415);
		REQUIRE( micheal[0] == 3.1415 );
	};
	SECTION("remove")
	{
		micheal.add(0, 3.1415);
		micheal.add(1, 2.7182);
		micheal.remove(0);
		REQUIRE( !micheal.has(0) );
		REQUIRE( micheal[1] == 2.7182 );
	};
	SECTION("get")
	{
		micheal.add(0, 3.1415);

		REQUIRE( micheal.get(0) == 3.1415 );
	};
	SECTION("has")
	{
		micheal.add(0, 3.1415);

		REQUIRE( micheal.has(0) );
		REQUIRE( !micheal.has(1) );
	};
};
