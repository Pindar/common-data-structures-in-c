extern "C"
{
#include "CppUTest/TestHarness_c.h"

#include "LinkedList.h"
#include "iterator.h"

}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LinkedList)
{

	LinkedList * list;

	void setup()
	{
		list = LinkedList_Create();
	}
	void teardown()
	{
		LinkedList_Destroy(list);
	}

};


TEST(LinkedList, remove)
{

	void * a = NULL;

	CHECK_EQUAL(0, LinkedList_size(list));

	a = LinkedList_remove(&list);
	CHECK_EQUAL(0, LinkedList_size(list));

	a = malloc(1);
	LinkedList_add(list, a);
	CHECK_EQUAL(1, LinkedList_size(list));

	a = LinkedList_remove(&list);
	CHECK(a != NULL);
	CHECK_EQUAL(0, LinkedList_size(list));
	free(a);


}

TEST(LinkedList, sizeANDaddANDremove) {

	void * a = malloc(1);
	void * b = malloc(1);
	void * c = malloc(1);
	void * d = malloc(1);
	void * r = NULL;

	CHECK_EQUAL(0, LinkedList_size(list));

	LinkedList_add(list, a);
	CHECK_EQUAL(1, LinkedList_size(list));

	LinkedList_add(list, b);
	CHECK_EQUAL(2, LinkedList_size(list));

	LinkedList_add(list, c);
	CHECK_EQUAL(3, LinkedList_size(list));

	LinkedList_add(list, d);
	CHECK_EQUAL(4, LinkedList_size(list));

	r = LinkedList_remove(&list);
	CHECK_EQUAL(a,r);
	CHECK_EQUAL(3, LinkedList_size(list));


	free(a);
	free(b);
	free(c);
	free(d);
}

TEST(LinkedList, get)
{

	void * a = malloc(1);
	void * b = malloc(1);
	void * check = NULL;

	LinkedList_add(list, a);
	CHECK_EQUAL(1, LinkedList_size(list));

	LinkedList_add(list, b);
	CHECK_EQUAL(2, LinkedList_size(list));

	check = LinkedList_get(list, 2);
	POINTERS_EQUAL(b, check);

	check = NULL;
	check = LinkedList_get(list, 1);
	POINTERS_EQUAL(a, check);


	free(a);
	free(b);
}

TEST(LinkedList, contains)
{
	//todo
}

TEST(LinkedList, removefirstoccurrence) {

	// todo
}

TEST(LinkedList, remove_last)
{
	void * item = NULL;
	int i;

	for (i = 0; i < 10; i += 1) {
		LinkedList_add(list, malloc(1));
	}
	CHECK_EQUAL_C_INT(10, LinkedList_size(list));


	for (item = LinkedList_remove_last(&list); item != NULL; item = LinkedList_remove_last(&list)) {
		free(item);
	}

	CHECK_EQUAL_C_INT(0, LinkedList_size(list));
}

TEST(LinkedList, remove_last_empty_list)
{
	CHECK_EQUAL_C_INT(0, LinkedList_size(list));
	CHECK(NULL == LinkedList_remove_last(&list));
	CHECK_EQUAL_C_INT(0, LinkedList_size(list));
}

TEST(LinkedList, remove_last_empty_parameter)
{
	CHECK(NULL == LinkedList_remove_last(NULL));
}

TEST(LinkedList, remove_last_two_items)
{
	char * result = NULL;
	char * item_1 = (char *) malloc(5 * sizeof(char));
	char * item_2 = (char *) malloc(5 * sizeof(char));
	strcpy(item_1, "test");
	strcpy(item_2, "tese");

	LinkedList_add(list, item_1);
	LinkedList_add(list, item_2);

	result = (char *) LinkedList_remove_last(&list);
	STRCMP_CONTAINS("tese", result);
	free(result);
	result = (char *) LinkedList_remove_last(&list);
	STRCMP_CONTAINS("test", result);
	free(result);

}

TEST(LinkedList, create_iterator)
{
	Iterator * it = LinkedList_iterator(list);
	CHECK(NULL != it);

	Iterator_Destroy(it);
}

TEST(LinkedList, iterator_has_next_empty)
{
	Iterator * it = LinkedList_iterator(list);

	CHECK(!Iterator_has_next(it));

	Iterator_Destroy(it);
}

TEST(LinkedList, iterator_has_next_true)
{
	int item = 42;
	LinkedList_add(list, &item);
	Iterator * it = LinkedList_iterator(list);

	CHECK(Iterator_has_next(it));

	Iterator_Destroy(it);
}

TEST(LinkedList, iterator_next_empty_list)
{
	Iterator * it = LinkedList_iterator(list);

	CHECK(NULL == Iterator_next(it));

	Iterator_Destroy(it);
}

TEST(LinkedList, iterator_next_item) {
	int item = 42;
	LinkedList_add(list, &item);
	Iterator * it = LinkedList_iterator(list);

	POINTERS_EQUAL(&item, Iterator_next(it));

	Iterator_Destroy(it);
}

TEST(LinkedList, iterator_next_item_with_two_items)
{
	int item_1 = 42, item_2 = 43;
	LinkedList_add(list, &item_1);
	LinkedList_add(list, &item_2);
	Iterator * it = LinkedList_iterator(list);

	POINTERS_EQUAL(&item_1, Iterator_next(it));
	POINTERS_EQUAL(&item_2, Iterator_next(it));

	Iterator_Destroy(it);
}
