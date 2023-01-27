#include "CSVParser.h"

template <typename... Args>
void parser::CSVParser<Args...>::CheckFile() {
    if (file_.bad() || file_.fail()) { throw FileError(); }
}

template <typename... Args>
parser::CSVParser<Args...>::CSVParser(std::ifstream& file) : file_ (file) , arg_count_ (sizeof...(Args)) { CheckFile(); }

template <typename... Args>
parser::CSVParser<Args...>::CSVParser(const CSVParser<Args...>& csvParser) {
    file_ = csvParser.file_;
    tuple_ = csvParser.tuple_;
    arg_count_ = csvParser.arg_count_;
}

template <typename... Args>
parser::CSVParser<Args...>::~CSVParser() { file_.close(); }

template <typename... Args>
void parser::CSVParser<Args...>::ReadNewTuple() {
    int cur_pos = 0;
    pline_.clear();
    cur_line.clear();
    cur_word.clear();

    std::getline(file_, cur_line);
    while (cur_line[cur_pos] != char_const::kNullTerm) {
        if (cur_line[cur_pos] == char_const::kDelim) {
            pline_.push_back(cur_word);
            cur_word.clear();
            ++cur_pos;
            continue;
        }
        cur_word += cur_line[cur_pos++];
    }

    tuple_ = phelper::ParsedLineToTuple(pline_, std::make_index_sequence<arg_count_>());
}

