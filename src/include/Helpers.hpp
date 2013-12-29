#ifndef HELPERS_HPP
#define HELPERS_HPP

template <class T>
T max(const T& a, const T& b){
  return (a>b)?a:b;
}

template <class T>
T min(const T& a, const T& b){
    return (a>b)?b:a;
}


#endif
