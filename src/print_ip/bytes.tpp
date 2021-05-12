/** @file */

/**
 * \brief print_ip for byte sequence: print byte by byte as unsigned int8
 * \param[in] ip byte sequence: short, int, long, etc
 */
template <typename T>
auto print_ip(T ip) -> decltype(
    std::declval<
        typename std::enable_if<std::is_convertible<T, int>::value, T>::type
      >(),
    void()
) {
  for (unsigned long i = sizeof(T); i > 1; i--) {
    std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + i - 1) << '.';
  }
  std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + 0) << std::endl;
}