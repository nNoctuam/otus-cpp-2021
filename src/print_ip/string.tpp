template <typename StringT>
typename std::enable_if<is_std_container<StringT>::value &&
                        is_string<StringT>::value,
    StringT>::type
print_ip(StringT ip) {
  std::cout << ip << std::endl;
  return ip;
}
