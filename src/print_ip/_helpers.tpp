template <typename T, typename = void>
struct is_std_container : std::false_type {};

template <typename T>
struct is_std_container<
    T, std::void_t<decltype(std::declval<T>().begin()),
                   decltype(std::declval<T>().end()), typename T::value_type>>
    : std::true_type {};

template <typename T, typename = void> struct is_string : std::false_type {};

template <typename T>
struct is_string<T, std::void_t<typename is_std_container<T>::type,
                                decltype(std::declval<T &>().c_str())>>
    : std::true_type {};

template <typename> struct is_tuple : std::false_type {};

template <typename... T> struct is_tuple<std::tuple<T...>> : std::true_type {};
