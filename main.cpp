#include "lib.h"

#include <iostream>
#include <list>
#include <tuple>
#include <vector>

template <typename T, typename = void>
struct is_std_container : std::false_type {};

template <typename T>
struct is_std_container<
    T, std::void_t<decltype(std::declval<T &>().begin()),
                   decltype(std::declval<T &>().end()), typename T::value_type>>
    : std::true_type {};

template <typename T, typename = void> struct is_string : std::false_type {};

template <typename T>
struct is_string<T, std::void_t<typename is_std_container<T>::type,
                                decltype(std::declval<T &>().c_str())>>
    : std::true_type {};

template <typename BytesT>
typename std::enable_if<std::is_convertible<BytesT, int>::value, BytesT>::type
print_ip(BytesT ip) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  for (unsigned long i = sizeof(BytesT); i > 1; i--) {
    std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + i - 1) << '.';
  }
  std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + 0) << std::endl;
  return ip;
}

template <typename ContainerT>
typename std::enable_if<is_std_container<ContainerT>::value &&
                            !is_string<ContainerT>::value,
                        ContainerT>::type
print_ip(ContainerT ip) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  if (ip.begin() != ip.end()) {
    std::cout << std::to_string(*ip.begin());
  }
  for (auto begin = ip.begin(), end = ip.end(); begin != end; begin++) {
    if (begin == ip.begin()) {
      continue;
    }
    std::cout << '.' << std::to_string(*begin);
  }
  std::cout << std::endl;
  return ip;
}

template <typename StringT>
typename std::enable_if<is_std_container<StringT>::value &&
                            is_string<StringT>::value,
                        StringT>::type
print_ip(StringT ip) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  std::cout << ip << std::endl;
  return ip;
}

int main(int, char **) {

  print_ip(char{-1});                             // 255
  print_ip(short{0});                             // 0.0
  print_ip(int{2130706433});                      // 127.0.0.1
  print_ip(long{8875824491850138409});            // 123.45.67.89.101.112.131.41
  print_ip(std::string{"Hello, World!"});         // Hello, World!
  print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
  print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
  //  print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0

  return 0;
}
