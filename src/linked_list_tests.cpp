#include <CppUTest/TestHarness.h>

#include "linked_list.h"

TEST_GROUP(linked_list) {
	linked_list *list;
	void setup() {
		list = linked_list_create();
	}

	void teardown() {
		linked_list_destroy(list);
	}
};


TEST(linked_list, initial_size_is_0) {
	CHECK(0 == linked_list_size(list));
}

#include <string.h>
int string_matches(const void* current, const void *expected) {
	return strcmp((char*)current, (char*)expected) == 0;
}

TEST(linked_list, find_with_function) {
	linked_list_add(list, (char*)"A");
	linked_list_add(list, (char*)"B");
	linked_list_add(list, (char*)"C");
	void* found = linked_list_find(list, string_matches, "B");
	CHECK(found != NULL);
}

TEST(linked_list, last_found_correctly) {
	linked_list_add(list, (char*)"A");
	linked_list_add(list, (char*)"B");
	linked_list_add(list, (char*)"C");
	CHECK_EQUAL_C_STRING("C", (char *)list_node_data(linked_list_last(list)));
}

TEST(linked_list, adding_increments_size) {
	linked_list_add(list, (char*)"");
	CHECK(1 == linked_list_size(list));
}

TEST(linked_list, can_iterate_over_list) {
	linked_list_add(list, (char*)"hello");
	linked_list_add(list, (char*)"world");
	list_iterator *iter = linked_list_begin(list);
	CHECK(linked_list_has_next(iter));
	CHECK_EQUAL_C_STRING("hello", (const char*)linked_list_next(iter));
	CHECK_EQUAL_C_STRING("world", (const char*)linked_list_next(iter));
	CHECK(0 == linked_list_has_next(iter));
	linked_list_end(iter);
}

struct test_list_node {
	char *data;
	list_node *next;
};

typedef void* (*f_ptr)(int, void(*)(void));

TEST(linked_list, open_up_opaque_structure) {
	linked_list_add(list, (char*)"hello");
	test_list_node *node = (test_list_node*)(linked_list_last(list));
	CHECK_EQUAL_C_STRING("hello", node->data);
}

#include <stdlib.h>
TEST(linked_list, auto_releases_memory_with_function_pointer) {
	linked_list_add(list, malloc(20));
	linked_list_release_destroy(list, free);
	list = NULL;
}
