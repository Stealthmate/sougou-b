#ifndef UTIL_HPP
#define UTIL_HPP

#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <iostream>

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

template<typename T1, typename T2, typename F> std::vector<T2> vecmap(const std::vector<T1> &v1, F &&f) {
  std::vector<T2> v2(v1.size());
  std::transform(v1.begin(), v1.end(), v2.begin(), [f](auto a) -> T2 { f((T1) a); });

  return v2;
}

#endif
