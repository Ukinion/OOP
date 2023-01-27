#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    parser::CSVParser<int, std::string> parser(file);
    for (auto i = parser.begin(); i < parser.end(); ++i) {
        std::cout << rs << std::endl;
    }

    return 0;
}
