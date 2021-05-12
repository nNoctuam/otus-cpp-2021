/** @file */

/**
 * \brief print_ip for string: print as is
 * \param[in] ip string
 */
template <typename T>
auto print_ip(T ip) -> decltype(
    std::declval<
        typename std::enable_if<is_std_container<T>::value && is_string<T>::value, T>::type
      >(),
    void()
) {
  std::cout << ip << std::endl;
}
