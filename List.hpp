#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert

template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  //default constructor
  List()
    : first(nullptr), last(nullptr), sizeOf(0) {}

  //copy constructor
  List(const List &other)
    : first(nullptr), last(nullptr), sizeOf(0) {
    copy_all(other);
  }

  //destructor
  ~List() {
    clear();
  }

  //assignment operator
  List &operator=(const List &rhs) {
    if (this != &rhs) {
      clear();
      copy_all(rhs);
    }
    return *this;
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  int size() const {
    return sizeOf;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T &front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T &back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *newNode = new Node(datum, nullptr, first);
    if (first != nullptr) {
      first->prev = newNode;
    } else {
      //list was empty
      last = newNode;
    }
    first = newNode;
    ++sizeOf;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *n = new Node(datum, last, nullptr);
    if (last != nullptr) {
      last->next = n;
    } else {
      //list was empty
      first = n;
    }
    last = n;
    ++sizeOf;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node *n = first;
    first = first->next;
    if (first != nullptr) {
      first->prev = nullptr;
    } else {
      //list became empty
      last = nullptr;
    }
    delete n;
    --sizeOf;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node *n = last;
    last = last->prev;
    if (last != nullptr) {
      last->next = nullptr;
    } else {
      //list became empty
      first = nullptr;
    }
    delete n;
    --sizeOf;
  }

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear() {
    Node *cur = first;
    while (cur != nullptr) {
      Node *next = cur->next;
      delete cur;
      cur = next;
    }
    first = nullptr;
    last = nullptr;
    sizeOf = 0;
  }

private:
  struct Node {
    Node *next;
    Node *prev;
    T datum;

    Node(const T &d, Node *p = nullptr, Node *n = nullptr)
      : next(n), prev(p), datum(d) {}
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    Node *cur = other.first;
    while (cur != nullptr) {
      push_back(cur->datum);
      cur = cur->next;
    }
  }

  Node *first; //points to first Node in list, or nullptr if list is empty
  Node *last;  //points to last Node in list, or nullptr if list is empty
  int sizeOf;  //number of elements in the list

public:
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    //default constructor
    //EFFECTS: sets both pointer members to null pointers
    Iterator()
      : list_ptr(nullptr), node_ptr(nullptr) {}


    //REQUIRES: Iterator is dereferenceable
    //EFFECTS: returns the underlying element by reference
    T &operator*() const {
      assert(node_ptr != nullptr);
      return node_ptr->datum;
    }

    //prefix ++ (e.g. ++it)
    // REQUIRES: Iterator is incrementable (not past-the-end)
    // EFFECTS: moves this Iterator to point to the next element
    //          and returns a reference to this Iterator
    Iterator &operator++() {
      assert(node_ptr != nullptr); // end() is not incrementable
      node_ptr = node_ptr->next;
      return *this;
    }

    // postfix ++ (e.g. it++)
    // REQUIRES: Iterator is incrementable (not past-the-end)
    // EFFECTS: moves this Iterator to point to the next element
    //          and returns a copy of the original Iterator
    Iterator operator++(int /*dummy*/) {
      Iterator copy = *this;
      operator++();
      return copy;
    }

    bool operator==(const Iterator &rhs) const {
      return list_ptr == rhs.list_ptr && node_ptr == rhs.node_ptr;
    }

    bool operator!=(const Iterator &rhs) const {
      return !(*this == rhs);
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator &operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decr
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    T *operator->() const {
      return &operator*();
    }

    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

  private:
    const List *list_ptr; // pointer to the List associated with this Iterator
    Node *node_ptr;       // current Iterator position is a List node

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np)
      : list_ptr(lp), node_ptr(np) {}

    friend class List;
  }; // List::Iterator

  // return an Iterator pointing to the first element
  Iterator begin() {
    return Iterator(this, first);
  }

  Iterator begin() const {
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() {
    return Iterator(this, nullptr);
  }

  Iterator end() const {
    return Iterator(this, nullptr);
  }

  // REQUIRES: i is a valid, dereferenceable iterator associated with this list
  // MODIFIES: invalidates all iterators to the removed element
  // EFFECTS: Removes a single element from the list container.
  //          Returns an iterator pointing to the element that followed the
  //          element erased by the function call
  Iterator erase(Iterator i) {
    assert(i.list_ptr == this);
    Node *n = i.node_ptr;
    assert(n != nullptr); // must be dereferenceable
    Node *next = n->next;

    if (n == first) {
      first = n->next;
    }
    if (n == last) {
      last = n->prev;
    }
    if (n->prev != nullptr) {
      n->prev->next = n->next;
    }
    if (n->next != nullptr) {
      n->next->prev = n->prev;
    }

    delete n;
    --sizeOf;

    return Iterator(this, next);
  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: Inserts datum before the element at the specified position.
  //          Returns an iterator to the newly inserted element.
  Iterator insert(Iterator i, const T &datum) {
    assert(i.list_ptr == this);

    Node *next = i.node_ptr;
    Node *prev = nullptr;

    if (next == nullptr) {
      // inserting at end
      prev = last;
    } else {
      prev = next->prev;
    }

    Node *n = new Node(datum, prev, next);

    if (prev != nullptr) {
      prev->next = n;
    } else {
      // insert to front
      first = n;
    }

    if (next != nullptr) {
      next->prev = n;
    } else {
      // insert @ back
      last = n;
    }

    ++sizeOf;
    return Iterator(this, n);
  }

}; //List

#endif //Do not remove this. Write all your code above this line.
