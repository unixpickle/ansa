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
    Link * next = NULL;
    Link * last = NULL;
  };
  
  /**
   * A representation of a position in the linked list. This abstracts the
   * iteration process through the nodes in a linked list.
   */
  class Iterator {
  public:
    Iterator & operator++() {
      // prefix increment
      assert(cur != NULL);
      cur = cur->next;
      return *this;
    }
    
    Iterator operator++(int) {
      // postfix increment
      assert(cur != NULL);
      Iterator copied(cur);
      (*this)++;
      return copied;
    }
    
    bool operator==(const Iterator & i) {
      return i.cur == cur;
    }
    
    bool operator!=(const Iterator & i) {
      return i.cur != cur;
    }
    
    T & operator*() {
      assert(cur != NULL);
      return cur->obj;
    }
    
  protected:
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
    return Iterator(NULL);
  }
  
  T * GetFirst() const {
    if (first) return first->obj;
    return NULL;
  }
  
  T * GetLast() const {
    if (last) return last->obj;
    return NULL;
  }
  
  void Add(Link * link) {
    assert(link->next == NULL && link->last == NULL);
    if (last) {
      last->next = link;
      link->last = last;
    } else {
      first = link;
    }
    last = link;
  }
  
  void AddFront(Link * link) {
    assert(link->next == NULL && link->last == NULL);
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
      last = first = NULL;
    } else if (link == first) {
      link->next->last = NULL;
      first = link->next;
    } else if (link == last) {
      link->last->next = NULL;
      last = link->last;
    } else {
      link->last->next = link->next;
      link->next->last = link->last;
    }
    link->next = link->last = NULL;
  }
  
  T * Pop() {
    if (last) {
      T * res = &last->obj;
      Remove(last);
      return res;
    }
    return NULL;
  }
  
  T * Shift() {
    if (first) {
      T * res = &first->obj;
      Remove(first);
      return res;
    }
    return NULL;
  }
  
private:
  Link * first = NULL;
  Link * last = NULL;
};

}

#endif
