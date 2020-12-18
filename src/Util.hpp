#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <string>

template<typename T> unsigned int argmax(const std::vector<T> &vec) {
  unsigned int imax = 0;
  T maxv = -1;
  for(unsigned int i = 0; i < vec.size(); i++) {
    if(maxv < vec[i]) {
      maxv = vec[i];
      imax = i;
    }
  }

  return imax;
}

template<typename T> std::string join(std::string sep, const std::vector<T> &vec) {
  std::string r;
  for(unsigned int i = 0; i < vec.size() - 1; i++) {
    r += std::to_string(vec[i]) + sep;
  }

  return r + std::to_string(vec[vec.size() - 1]);
}

#endif
