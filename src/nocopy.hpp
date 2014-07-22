#ifndef __ANSA_NOCOPY_HPP__
#define __ANSA_NOCOPY_HPP__

namespace ansa {

class NoCopy {
public:
  NoCopy(const NoCopy &) = delete;
  NoCopy & operator=(const NoCopy &) = delete;
};

}

#endif
