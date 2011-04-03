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
	CHECK_EQUAL_C_INT(0, Array_list_get_capacity(NULL));
}

//TEST(array_list, create_with_capacity_less_zero)
//{
//	POINTERS_EQUAL(NULL, Array_list_Create(-1));
//}

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

	CHECK_EQUAL_C_INT(ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION, Array_list_add_on_index(NULL, 0, &test_value));
	CHECK_EQUAL_C_INT(ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION, Array_list_add_on_index(mlist, 0, NULL));
}

TEST(array_list, add_two_items_at_same_idx)
{
	int test_value_1 = 42,
		test_value_2 = 43;
	CHECK_EQUAL_C_INT(ARRAY_LIST_OK, Array_list_add_on_index(mlist, 0, &test_value_1));
	CHECK_EQUAL_C_INT(ARRAY_LIST_OK, Array_list_add_on_index(mlist, 0, &test_value_2));
	CHECK_EQUAL_C_INT(2, Array_list_size(mlist));
}

TEST(array_list, get_element_at_specific_position)
{
	int test_value_1 = 42;
	int * check_buf;

	Array_list_add_on_index(mlist, 0, &test_value_1);
	check_buf = static_cast <int*> (Array_list_get(mlist, 0));
	POINTERS_EQUAL(&test_value_1, check_buf);
	CHECK_EQUAL_C_INT(test_value_1, (*check_buf));
}

TEST(array_list, get_element_at_specific_position_illegal_argument_1)
{
	POINTERS_EQUAL(NULL, Array_list_get(mlist, 0));
}

TEST(array_list, get_element_at_specific_position_illegal_argument_2)
{
	int test_value_1 = 42;

	Array_list_add_on_index(mlist, 0, &test_value_1);
	POINTERS_EQUAL(NULL, Array_list_get(NULL, 0));
}

TEST(array_list, get_element_from_empty_array)
{
	POINTERS_EQUAL(NULL, Array_list_get(mlist, 0));
}

TEST(array_list, add_element_and_doubple_capacity)
{
	int test_value_1 = 42,
		test_value_2 = 43;

	Array_list * l_list = Array_list_Create(1);
	Array_list_add_on_index(l_list, 0, &test_value_1);
	Array_list_add_on_index(l_list, 0, &test_value_2);

	CHECK_EQUAL_C_INT(2, Array_list_get_capacity(l_list));
	Array_list_Destroy(l_list);
}

TEST(array_list, remove_last)
{
	int test_value_1 = 42,
		test_value_2 = 43;
	int * check_buf;

	Array_list_add_on_index(mlist, 0, &test_value_1);
	CHECK_EQUAL_C_INT(1, Array_list_size(mlist));
	Array_list_add_on_index(mlist, 1, &test_value_2);

	CHECK_EQUAL_C_INT(2, Array_list_size(mlist));

	check_buf = static_cast <int*> (Array_list_remove_last(mlist));
	CHECK_EQUAL_C_INT(test_value_2, *check_buf);
	CHECK_EQUAL_C_INT(1, Array_list_size(mlist));

	check_buf = static_cast <int*> (Array_list_remove_last(mlist));
	CHECK_EQUAL_C_INT(test_value_1, *check_buf);
	CHECK_EQUAL_C_INT(0, Array_list_size(mlist));
}

TEST(array_list, create_iterator)
{
	Iterator * it = Array_list_iterator(mlist);
	CHECK(NULL != it);
	Iterator_Destroy(it);
}

TEST(array_list, create_iterator_with_wrong_argument)
{
	Iterator * it = Array_list_iterator(NULL);
	POINTERS_EQUAL(NULL, it);
}

TEST(array_list, test_has_next_on_empty_list)
{
	Iterator * it = Array_list_iterator(mlist);

	CHECK(!Iterator_has_next(it));

	Iterator_Destroy(it);
}

TEST(array_list, test_has_next_on_list_with_one_item)
{
	int item = 42;
	Array_list_add_on_index(mlist, 0, &item);
	Iterator * it = Array_list_iterator(mlist);

	CHECK(Iterator_has_next(it));

	Iterator_Destroy(it);
}

TEST(array_list, test_get_next_on_empty_list)
{
	Iterator * it = Array_list_iterator(mlist);

	POINTERS_EQUAL(NULL, Iterator_next(it));

	Iterator_Destroy(it);
}

TEST(array_list, test_next_function_on_list_with_two_items)
{
	int item_1 = 42, item_2 = 43;
	Array_list_add_on_index(mlist, 0, &item_1);
	Array_list_add_on_index(mlist, 1, &item_2);
	Iterator * it = Array_list_iterator(mlist);

	POINTERS_EQUAL(&item_1, Iterator_next(it));
	POINTERS_EQUAL(&item_2, Iterator_next(it));

	Iterator_Destroy(it);
}
