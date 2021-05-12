/** @file */

/**
 * \brief print_ip for tuple of elements of the same type: print
 *        one by one as is
 * \param[in] ip tuple
 */
template <int SIZE, int RPOS, typename T>
typename std::enable_if<RPOS == 0, T>::type print_tuple_elements(const T &ip) {
  return ip;
}

template <int SIZE, int RPOS, typename T>
typename std::enable_if<is_tuple<T>::value && RPOS != 0, T>::type
print_tuple_elements(const T &ip) {
  static_assert(std::is_same<typename std::tuple_element<SIZE - RPOS, T>::type,
                             typename std::tuple_element<0, T>::type>::value,
                "Tuple elements must be of the same type");
  std::cout << '.' << std::get<SIZE - RPOS>(ip);
  print_tuple_elements<SIZE, RPOS - 1, T>(ip);
  return ip;
}

template <typename T>
typename std::enable_if<is_tuple<T>::value, T>::type print_ip(T ip) {
  std::cout << std::get<0>(ip);
  constexpr int size = std::tuple_size<T>();
  print_tuple_elements<size, size - 1, T>(ip);
  std::cout << std::endl;
  return ip;
}