/** @file */

/**
 * \brief print_ip for stl container (vector, list, etc): print element by element as is
 * \param[in] ip stl container
 */
template <typename T>
typename std::enable_if<is_std_container<T>::value && !is_string<T>::value,
                        T>::type
print_ip(T ip) {
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