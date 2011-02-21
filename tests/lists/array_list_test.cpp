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
	CHECK_EQUAL_C_INT(ARRAY_LIST_DEFAULT_INIT_SIZE, Array_list_get_size(list));
}

TEST(array_list, size_with_null_parameter) {
	CHECK_EQUAL_C_INT(-1, Array_list_get_size(NULL));
}

TEST(array_list, create_with_size_less_zero)
{
	POINTERS_EQUAL(NULL, Array_list_Create(-1));
}

TEST(array_list, create_with_custom_size)
{
	Array_list * l_list = Array_list_Create(256);
	CHECK_EQUAL_C_INT(256, Array_list_get_size(l_list));

	Array_list_Destroy(l_list);
}

