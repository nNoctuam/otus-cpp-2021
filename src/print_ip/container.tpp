template <typename ContainerT>
typename std::enable_if<is_std_container<ContainerT>::value &&
                        !is_string<ContainerT>::value,
    ContainerT>::type
print_ip(ContainerT ip) {
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