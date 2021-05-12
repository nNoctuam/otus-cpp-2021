/** @file */

/**
 * \brief print_ip for string: print as is
 * \param[in] ip string
 */
template <typename T>
typename std::enable_if<is_std_container<T>::value && is_string<T>::value,
                        T>::type
print_ip(T ip) {
  std::cout << ip << std::endl;
  return ip;
}
