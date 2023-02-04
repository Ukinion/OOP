#pragma once

#include <iostream>
#include <tuple>
#include <fstream>

template <typename Ch, typename Tr, size_t pos_int_tuple, typename... Args>
class Printer
{
public:
    static std::basic_ostream<Ch, Tr>& PrintTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple)
    {
        Printer<Ch, Tr, pos_int_tuple - 1, Args...>::PrintTuple(os, tuple);
        return os << std::get<pos_int_tuple - 1>(tuple) << ' ';
    }
};

template <typename Ch, typename Tr, typename... Args>
class Printer<Ch, Tr, 1, Args...>
{
public:
    static std::basic_ostream<Ch, Tr>& PrintTuple (std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple)
    { return os << std::get<0>(tuple) << ' '; }
};

template <typename Ch, typename Tr>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<> const& t) { return os; }

template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& tuple)
{ return Printer<Ch, Tr, sizeof...(Args), Args...>::PrintTuple(os, tuple); }
