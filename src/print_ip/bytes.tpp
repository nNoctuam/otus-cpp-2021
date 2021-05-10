template <typename T>
typename std::enable_if<std::is_convertible<T, int>::value, T>::type
print_ip(T ip) {
  for (unsigned long i = sizeof(T); i > 1; i--) {
    std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + i - 1) << '.';
  }
  std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + 0) << std::endl;
  return ip;
}