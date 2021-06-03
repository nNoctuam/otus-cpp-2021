/** @file */

/**
 * \brief print_ip for stl container (vector, list, etc): print
 *        element by element as is
 * \param[in] ip stl container
 */
template <typename T>
auto print_ip(T ip) -> decltype(
    std::declval<
        typename std::enable_if<is_std_container<T>::value && !is_string<T>::value, T>::type
      >(),
    void()
) {
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
}