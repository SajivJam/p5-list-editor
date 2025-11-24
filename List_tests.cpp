#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

// checks if empty -> default constructor creates an empty list
TEST(test_empty_list) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

// adds and removes element from the front of the list
TEST(test_push_pop_front) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    ASSERT_EQUAL(list.front(), 2);
    list.pop_front();
    ASSERT_EQUAL(list.front(), 1);
}

// adds and removes element from the back of the list
TEST(test_push_pop_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    ASSERT_EQUAL(list.back(), 2);
    list.pop_back();
    ASSERT_EQUAL(list.back(), 1);
}

// makes a deep copy of list1 into list2 with copy constructor
TEST(test_copy_constructor_deep_copy) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    List<int> list2(list1);

    list2.push_back(3);
    list2.pop_front();

    ASSERT_EQUAL(list1.size(), 2);
    ASSERT_EQUAL(list1.front(), 1);
    ASSERT_EQUAL(list1.back(), 2);

    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list2.front(), 2);
    ASSERT_EQUAL(list2.back(), 3);
}

// assigns list1 to list2 to check if you can copy via assignment operator
TEST(test_assignment) {
    List<int> list1;
    list1.push_back(1);
    List<int> list2;
    list2 = list1;
    ASSERT_EQUAL(list2.front(), 1);
}

// uses traveral by iterator to check elements in the list
TEST(test_iterator_basic) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
}

// inserts an element in the middle of the list
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

// removes an element from the middle of the list
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

TEST(test_single_element_operations) {
    List<int> list;
    list.push_back(42);
    ASSERT_EQUAL(list.front(), 42);
    ASSERT_EQUAL(list.back(), 42);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_FALSE(list.empty());
}

TEST(test_push_front_updates_last) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(list.back(), 1); 
}

TEST(test_push_back_updates_first) {
    List<int> list;
    list.push_back(1);
    ASSERT_EQUAL(list.front(), 1);
}

TEST(test_pop_until_empty) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.pop_back();
    list.pop_back();
    ASSERT_TRUE(list.empty());
}

TEST(test_pop_front_until_empty) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.pop_front();
    list.pop_front();
    ASSERT_TRUE(list.empty()); 
}

TEST(test_size_tracking) {
    List<int> list;
    ASSERT_EQUAL(list.size(), 0);
    list.push_back(1);
    ASSERT_EQUAL(list.size(), 1);
    list.push_back(2);
    ASSERT_EQUAL(list.size(), 2);
    list.pop_front();
    ASSERT_EQUAL(list.size(), 1);
    list.pop_back();
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_iterator_empty_list) {
    List<int> list;
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_insert_returns_iterator) {
    List<int> list;
    list.push_back(2);
    List<int>::Iterator it = list.insert(list.begin(), 1);
    ASSERT_EQUAL(*it, 1); 
}

TEST(test_erase_last_element) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    List<int>::Iterator it = list.begin();
    ++it;
    list.erase(it);
    ASSERT_EQUAL(list.back(), 1); 
}

TEST(test_copy_independence) {
    List<int> list1;
    list1.push_back(1);
    List<int> list2(list1);
    list2.pop_back();
    ASSERT_EQUAL(list1.size(), 1); 
}

TEST(test_assignment_clears_old) {
    List<int> list1;
    list1.push_back(1);
    List<int> list2;
    list2.push_back(99);
    list2.push_back(88);
    list2 = list1;
    ASSERT_EQUAL(list2.size(), 1);
    ASSERT_EQUAL(list2.front(), 1);
}

TEST(test_insert_empty_list) {
    List<int> list;
    list.insert(list.end(), 1);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 1);
}

TEST(test_erase_first_updates_pointer) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.erase(list.begin());
    ASSERT_EQUAL(list.front(), 2);
}

TEST(test_iterator_end_after_erase) {
    List<int> list;
    list.push_back(1);
    List<int>::Iterator it = list.erase(list.begin());
    ASSERT_TRUE(it == list.end()); 
}

TEST(test_clear_function) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.clear();
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

TEST(test_iterator_modify_element) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    List<int>::Iterator it = list.begin();
    *it = 10;
    ASSERT_EQUAL(list.front(), 10);
    
    ++it;
    *it = 20;
    ASSERT_EQUAL(*it, 20);
}

TEST(test_prefix_increment_returns_self) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    
    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = ++it1; 

    ASSERT_EQUAL(*it1, 2);
    ASSERT_EQUAL(*it2, 2);
    ASSERT_TRUE(it1 == it2);
}

TEST(test_reuse_after_clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();

    list.push_back(3);
    list.push_back(4);
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 3);
    ASSERT_EQUAL(list.back(), 4);
}

TEST(test_postfix_returns_copy) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    List<int>::Iterator it = list.begin();
    List<int>::Iterator old = it++;
    
    ASSERT_EQUAL(*old, 1);
    ASSERT_EQUAL(*it, 2);
    ASSERT_FALSE(old == it);
}

TEST(test_iterator_inequality) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    
    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();
    ++it2;
    
    ASSERT_TRUE(it1 != it2);
    ASSERT_FALSE(it1 != list.begin());
}

TEST(test_self_assignment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    list = list;
    
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);
}

TEST(test_assignment_empty_to_nonempty) {
    List<int> list1;
    
    List<int> list2;
    list2.push_back(99);
    list2.push_back(88);
    
    list2 = list1; 

    ASSERT_TRUE(list2.empty());
    ASSERT_EQUAL(list2.size(), 0);
}

TEST(test_assignment_return_value) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    
    List<int> list2;
    List<int> list3;
    
    list3 = list2 = list1;
    
    ASSERT_EQUAL(list3.size(), 2);
    ASSERT_EQUAL(list3.front(), 1);
    ASSERT_EQUAL(list3.back(), 2);
    
    ASSERT_EQUAL(list2.size(), 2);
    ASSERT_EQUAL(list2.front(), 1);
}

TEST(test_erase_only_element) {
    List<int> list;
    list.push_back(42);
    
    List<int>::Iterator it = list.erase(list.begin());
    
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(it == list.end());
}

TEST(test_empty_transitions) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    
    list.push_back(1);
    ASSERT_FALSE(list.empty());
    
    list.push_back(2);
    ASSERT_FALSE(list.empty());
    
    list.pop_front();
    ASSERT_FALSE(list.empty());
    
    list.pop_front();
    ASSERT_TRUE(list.empty());
}

TEST_MAIN()
