#ifndef __ANSA_ENABLE_IF_HPP__
#define __ANSA_ENABLE_IF_HPP__

namespace ansa {

template <bool B, class T = void>
struct EnableIf;

template <class T>
struct EnableIf<true, T> {
  typedef T type;
};

template <class T>
struct EnableIf<false, T> {
};

}

#endif
