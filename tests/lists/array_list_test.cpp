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

	Array_list * mlist;

	void setup()
	{
		mlist = Array_list_Create(0);
	}
	void teardown()
	{
		Array_list_Destroy(mlist);
	}
};

TEST(array_list, create_destroy)
{
	CHECK(mlist != NULL);
	CHECK_EQUAL_C_INT(ARRAY_LIST_DEFAULT_INIT_SIZE, Array_list_get_capacity(mlist));
}

TEST(array_list, capacity_with_null_parameter) {
	CHECK_EQUAL_C_INT(-1, Array_list_get_capacity(NULL));
}

TEST(array_list, create_with_capacity_less_zero)
{
	POINTERS_EQUAL(NULL, Array_list_Create(-1));
}

TEST(array_list, create_with_custom_size)
{
	Array_list * l_list = Array_list_Create(256);
	CHECK_EQUAL_C_INT(256, Array_list_get_capacity(l_list));

	Array_list_Destroy(l_list);
}

TEST(array_list, check_size)
{
	CHECK_EQUAL_C_INT(0, Array_list_size(mlist));
}

TEST(array_list, add_one_item)
{
	int test_value = 42;
	Array_list_add_on_index(mlist, 0, &test_value);
	CHECK_EQUAL_C_INT(1, Array_list_size(mlist));
}

TEST(array_list, add_exceptions)
{
	int test_value = 42;
	CHECK_EQUAL_C_INT(ARRAY_LIST_INDEX_OUT_OF_BOUNDS_EXCEPTION, Array_list_add_on_index(mlist, -1, &test_value));

	CHECK_EQUAL_C_INT(ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION, Array_list_add_on_index(NULL, 0, &test_value));
	CHECK_EQUAL_C_INT(ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION, Array_list_add_on_index(mlist, 0, NULL));
}

IGNORE_TEST(array_list, add_two_items_at_same_idx)
{
	int test_value_1 = 42,
		test_value_2 = 43;
	CHECK_EQUAL_C_INT(ARRAY_LIST_OK, Array_list_add_on_index(mlist, 0, &test_value_1));
	CHECK_EQUAL_C_INT(ARRAY_LIST_OK, Array_list_add_on_index(mlist, 0, &test_value_2));
	CHECK_EQUAL_C_INT(2, Array_list_size(mlist));

}

