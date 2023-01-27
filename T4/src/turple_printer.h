#pragma once

#include <iostream>
#include <tuple>
#include <fstream>

template <typename Ch, typename Tr, size_t last_pos_in_tuple, typename... Args>
struct Printer {
  static std::basic_ostream<Ch, Tr>& tuple_print(
      std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple) {
    Printer<Ch, Tr, last_pos_in_tuple - 1, Args...>::tuple_print(os, tuple);
    return os << std::get<last_pos_in_tuple - 1>(tuple) << '|';
  }
};

template <typename Ch, typename Tr, typename... Args>
struct Printer<Ch, Tr, 1, Args...> {
  static std::basic_ostream<Ch, Tr>& tuple_print(
      std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple) {
    return os << std::get<0>(tuple) << '|';
  }
};

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os,
                                       std::tuple<> const& t) {
  return os;
}

template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os,
                                       std::tuple<Args...> const& tuple) {
  return Printer<Ch, Tr, sizeof...(Args), Args...>::tuple_print(os, tuple);
}
