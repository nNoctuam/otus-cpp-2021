template <typename BytesT>
typename std::enable_if<std::is_convertible<BytesT, int>::value, BytesT>::type
print_ip(BytesT ip) {
  for (unsigned long i = sizeof(BytesT); i > 1; i--) {
    std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + i - 1) << '.';
  }
  std::cout << (uint) * (reinterpret_cast<uint8_t *>(&ip) + 0) << std::endl;
  return ip;
}