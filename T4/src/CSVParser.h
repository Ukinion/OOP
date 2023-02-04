#pragma once

#include "tuple_printer.h"
#include "exceptions.h"
#include <vector>

typedef std::vector<std::string> ParsedLine;

namespace char_const
{
    constexpr auto kDelim = ' ';
    constexpr auto kFloatPoint = '.';
    constexpr auto kMinus = '-';
    constexpr auto kControlSymbol = '|';
}

namespace int_const
{
    constexpr auto kIntMax = 2147483647;
    constexpr auto kIntMin = -2147483648;
}

namespace phelper
{
    template <typename T>
    T DefineDataType(std::string& str, int col, int row) { throw UnknownDataType(); }

    template<>
    std::string DefineDataType<std::string>(std::string& str, int col, int row)
    {
        if (str.size() == 1) { throw UnsupportedDataFormat(col, row, "std::string"); }

        try {
            int char_count = 0;

            for (char cur_sym: str) {
                if (!std::isdigit(cur_sym)) { ++char_count; }
                if (char_count > 1 && *str.begin() != char_const::kMinus) { throw ValidStringFormat(); }
            }
            throw UnsupportedDataFormat(col, row, "std::string");
        }
        catch (const ValidStringFormat& ex) { return str; }
    }

    template<>
    char DefineDataType<char>(std::string& str, int col, int row)
    {
        if (str.size() == 1) { return *str.begin(); }
        else { throw UnsupportedDataFormat(col, row, "char"); }
    }

    template <>
    double DefineDataType<double>(std::string& str, int col, int row)
    {
        using namespace std;
        int minus_count = 0;
        int fpoint_count = 0;

        for (char cur_sym : str)
        {
            if (!isdigit(cur_sym))
            {
                if (cur_sym == char_const::kFloatPoint) { ++fpoint_count; continue; }
                if (cur_sym == char_const::kMinus) { ++minus_count; continue;}
                throw UnsupportedDataFormat(col, row, "double");
            }
            if (fpoint_count > 1 || minus_count > 1) { throw UnsupportedDataFormat(col, row, "double"); }
        }
        return stod(str);
    }

    template<>
    int DefineDataType<int>(std::string& str, int col, int row)
    {
        for (char cur_sym : str)
        {
            if (!std::isdigit(cur_sym) && *str.begin() != char_const::kMinus)
            { throw UnsupportedDataFormat(col, row, "int"); }
        }

        auto data= std::stoll(str);
        if (data > int_const::kIntMax || data < int_const::kIntMin)
        { throw UnsupportedDataFormat(col, row, "int"); }

        return static_cast<int>(data);
    }

    template<>
    long long DefineDataType<long long>(std::string& str, int col, int row)
    {
        for (auto iter = str.begin(); iter < str.end(); ++iter)
        {
            if (!std::isdigit(*iter) && iter != str.begin() || *iter != char_const::kMinus && iter == str.begin())
            { throw UnsupportedDataFormat(col, row, "long long"); }
        }

        auto data = std::stoll(str);
        if (data < int_const::kIntMax && data > int_const::kIntMin)
        { throw UnsupportedDataFormat(col, row, "long long"); }

        return data;
    }

    template <typename... Args, size_t... Is>
    std::tuple<Args...> ParsedLineToTuple(ParsedLine& pline, std::index_sequence<Is...>, int row)
    { return std::make_tuple((DefineDataType<Args>(pline[Is], Is+1, row))...); }
}

namespace parser
{
    template<typename... Args>
    class Iterator;

    template<typename... Args>
    class CSVParser
    {
    public:
        friend class Iterator<Args...>;

        CSVParser(std::ifstream *file, int skip_lines) : file_ (file)
        {
            row_ = 0;
            CheckFile();
            std::string string;
            for (int i = 0; i < skip_lines; ++i) { std::getline(*file_, string); }
        }

        CSVParser(const CSVParser<Args...> &parser1) = default;
        ~CSVParser() { file_->close(); }

        Iterator<Args...> begin() { return Iterator<Args...>(this, false); }
        Iterator<Args...> end() { return Iterator<Args...>(this, true); }

        void ReadNewTuple()
        {
            int col_count = 0;
            std::string cur_line;
            std::string cur_word;

            pline_.clear();
            std::getline(*file_, cur_line);
            ++row_;

            for (char cur_sym : cur_line)
            {
                if (cur_sym == char_const::kDelim || cur_sym == char_const::kControlSymbol)
                {
                    pline_.push_back(cur_word);
                    cur_word.clear();
                    ++col_count;
                }
                else { cur_word += cur_sym; }
            }

            if (col_count != args_count_) { throw InvalidCountOfArgs(row_, args_count_, col_count); }

            tuple_ = phelper::ParsedLineToTuple<Args...>(pline_, std::make_index_sequence<args_count_>(), row_);
        }
    private:
        int row_;
        static const size_t args_count_ = sizeof...(Args);

        std::tuple<Args...> tuple_;
        std::ifstream* file_;
        ParsedLine pline_;

        void CheckFile() { if (file_->bad() || file_->fail()) { throw FileError(); }}
    };

    template<typename... Args>
    class Iterator
    {
    public:
        using TuplePtr = std::tuple<Args...>*;
        using TupleRef = std::tuple<Args...>&;
        using CSVptr = parser::CSVParser<Args...>*;

        Iterator(CSVptr csvParser, bool end) : csvParser_ (csvParser)
        {
            if (end || csvParser_->file_->eof()) { end_ = true; }
            else { csvParser->ReadNewTuple(); }
        }

        TuplePtr operator->() { return &csvParser_->tuple_; };

        TupleRef operator*() { return csvParser_->tuple_; };

        Iterator& operator++()
        {
            if (csvParser_->file_->eof()) { end_ = true; }
            else { csvParser_->ReadNewTuple(); }
            return *this;
        }

        friend bool operator==(const Iterator &it1, const Iterator &it2) { return (it1.end_ && it2.end_); }
        friend bool operator!=(const Iterator &it1, const Iterator &it2) { return !(it1 == it2); }
    private:
        CSVptr csvParser_;
        bool end_;
    };
}
