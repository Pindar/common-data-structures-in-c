/*
 * array_list_test.cpp
 *
 *  Created on: 21.02.2011
 *      Author: simon
 */

extern "C"
{
#include "CppUTest/TestHarness_c.h"
#include "array_list.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(array_list)
{

	Array_list * list;

	void setup()
	{
		list = Array_list_Create(0);
	}
	void teardown()
	{
		Array_list_Destroy(list);
	}
};

TEST(array_list, create_destroy)
{
	CHECK(list != NULL);
}
