template <int SIZE, int RPOS, typename TupleT>
typename std::enable_if<RPOS == 0, TupleT>::type
print_tuple_elements(const TupleT &ip) {
  return ip;
}

template <int SIZE, int RPOS, typename TupleT>
typename std::enable_if<is_tuple<TupleT>::value && RPOS != 0, TupleT>::type
print_tuple_elements(const TupleT &ip) {
  std::cout << '.' << std::get<SIZE - RPOS>(ip);
  print_tuple_elements<SIZE, RPOS - 1, TupleT>(ip);
  return ip;
}

template <typename TupleT>
typename std::enable_if<is_tuple<TupleT>::value, TupleT>::type
print_ip(TupleT ip) {
  std::cout << std::get<0>(ip);
  constexpr int size = std::tuple_size<TupleT>();
  print_tuple_elements<size, size - 1, TupleT>(ip);
  std::cout << std::endl;
  return ip;
}