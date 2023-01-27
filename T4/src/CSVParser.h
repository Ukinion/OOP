#pragma once

#include "tuple_printer.h"
#include "exceptions.h"
#include <vector>

typedef std::vector<std::string> ParsedLine;

namespace char_const {
    constexpr auto kNullTerm = '\0';
    constexpr auto kDelim = ' ';
}

namespace phelper {
    template <typename T>
    T ConvertString(std::string& str, size_t Is) { throw UnsupportedDataFormat (); }

    template <>
    std::string ConvertString<std::string>(std::string& str, size_t Is) { return str; }

    template <>
    int ConvertString<int>(std::string& str, size_t Is) {
        for (char i : str)
            if (!std::isdigit(i)) { throw(InvalidDataFormat{"int"}); }
        return std::stoi(str);
    }

    template <typename... Args, size_t... Is>
    std::tuple<Args...> ParsedLineToTuple(ParsedLine &pline, std::index_sequence<Is...>) {
        return std::make_tuple((ConvertString<Args>(pline[Is], Is+1))...);
    }
}

namespace parser {
    template<typename... Args>
    class CSVParser {
    public:
        CSVParser(std::ifstream&);
        CSVParser(const CSVParser<Args...>&);
        ~CSVParser();

        class Iterator {
        public:
            using pointer = std::tuple<Args...>*;
            using reference = std::tuple<Args...>&;

            Iterator(pointer ptr, CSVParser& csvParser, bool end) : ptr_ (ptr), csvParser_ (csvParser) {
                if (end || csvParser_.file.eof()) { end_ = true; }
                else { csvParser.ReadNewTuple(); }
            }

            pointer operator->() { return ptr_; };
            reference operator*() { return *ptr_; };

            Iterator& operator++() {
                if (csvParser_.file.eof()) { end_ = true; }
                else { csvParser_.ReadNewTuple(); return *this; }
            }

            Iterator operator++(int) { return ++(*this); }

            friend bool operator==(const Iterator& it1, const Iterator& it2) {
                return it1.end_ && it2.end_;
            }

            friend bool operator!=(const Iterator& it1, const Iterator& it2) {
                 return !(it1 == it2);
            }

        private:
            pointer ptr_;
            CSVParser& csvParser_;
            bool end_;
        };

        Iterator begin() { return Iterator(&tuple_, *this, false); }
        Iterator end() { return Iterator(&tuple_, *this, true); }

        void ReadNewTuple();
    private:
        void CheckFile();

        ParsedLine pline_;
        std::string cur_line;
        std::string cur_word;

        std::tuple<Args...> tuple_;
        std::ifstream& file_;
        const size_t arg_count_;
    };
}
