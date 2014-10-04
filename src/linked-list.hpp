#ifndef __ANSA_LINKED_LIST_HPP__
#define __ANSA_LINKED_LIST_HPP__

#include <cassert>
#include <cstddef>

namespace ansa {

template <class T>
class LinkedList {
public:
  /**
   * A link in the linked list. Links must be allocated externally. To simplify
   * things, I suggest making the link a member of the element's class.
   */
  struct Link {
    Link(T & o) : obj(o) {}
    
    T & obj;
    Link * next = nullptr;
    Link * last = nullptr;
  };
  
  /**
   * A representation of a position in the linked list. This abstracts the
   * iteration process through the nodes in a linked list.
   */
  class Iterator {
  public:
    Iterator & operator++() {
      // prefix increment
      assert(cur != nullptr);
      cur = cur->next;
      return *this;
    }
    
    Iterator operator++(int) {
      // postfix increment
      assert(cur != nullptr);
      Iterator copied(cur);
      ++(*this);
      return copied;
    }
    
    bool operator==(const Iterator & i) {
      return i.cur == cur;
    }
    
    bool operator!=(const Iterator & i) {
      return i.cur != cur;
    }
    
    T & operator*() {
      assert(cur != nullptr);
      return cur->obj;
    }
    
  protected:
    friend class LinkedList;
    Iterator(Link * c) : cur(c) {}
    Link * cur;
  };
  
  /**
   * Get the iterator for the start of the list. If the list is empty, this
   * will be equal to the result of [GetEnd].
   */
  Iterator GetStart() const {
    return Iterator(first);
  }
  
  /**
   * Return the iterator for the end of the list, directly after the last
   * element. This iterator should not be dereferenced or incremented.
   */
  Iterator GetEnd() const {
    return Iterator(nullptr);
  }
  
  T * GetFirst() const {
    if (first) return &first->obj;
    return nullptr;
  }
  
  T * GetLast() const {
    if (last) return &last->obj;
    return nullptr;
  }
  
  void Add(Link * link) {
    assert(link->next == nullptr && link->last == nullptr);
    if (last) {
      last->next = link;
      link->last = last;
    } else {
      first = link;
    }
    last = link;
  }
  
  void AddFront(Link * link) {
    assert(link->next == nullptr && link->last == nullptr);
    if (first) {
      first->last = link;
      link->next = first;
    } else {
      last = link;
    }
    first = link;
  }
  
  void Remove(Link * link) {
    if (link == first && link == last) {
      last = first = nullptr;
    } else if (link == first) {
      link->next->last = nullptr;
      first = link->next;
    } else if (link == last) {
      link->last->next = nullptr;
      last = link->last;
    } else {
      link->last->next = link->next;
      link->next->last = link->last;
    }
    link->next = link->last = nullptr;
  }
  
  T * Pop() {
    if (last) {
      T * res = &last->obj;
      Remove(last);
      return res;
    }
    return nullptr;
  }
  
  T * Shift() {
    if (first) {
      T * res = &first->obj;
      Remove(first);
      return res;
    }
    return nullptr;
  }
  
private:
  Link * first = nullptr;
  Link * last = nullptr;
};

}

#endif
