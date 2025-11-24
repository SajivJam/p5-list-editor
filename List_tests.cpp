#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here
TEST(test_empty_list) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_push_pop_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    ASSERT_EQUAL(list.front(), 2);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 1);
}

TEST(test_push_pop_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    ASSERT_EQUAL(list.back(), 2);
    list.pop_back();
    ASSERT_EQUAL(list.back(), 1);
}

TEST(test_copy_constructor) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    List<int> list2(list1);
    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list2.front(), 1);
}

TEST(test_assignment) {
    List<int> list1;
    list1.push_back(1);
    List<int> list2;
    list2 = list1;
    ASSERT_EQUAL(list2.front(), 1);
}

TEST(test_iterator_basic) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
}

TEST(test_insert) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    List<int>::Iterator it = list.begin();
    ++it;
    list.insert(it, 2);
    it = list.begin();
    ++it;
    ASSERT_EQUAL(*it, 2);
}

TEST(test_erase) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator it = list.begin();
    ++it;
    list.erase(it);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST_MAIN()
