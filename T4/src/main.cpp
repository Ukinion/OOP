#include "CSVParser.h"

int main()
{
    try
    {
        std::ifstream file("test.txt");
        parser::CSVParser<int, double, long long> csvParser(&file, 0);
        for (auto& it : csvParser)
        {
            std::cout << it << std::endl;
        }
    }
    catch (const UnsupportedDataFormat& e)
    {
        std::cout << e.what();
    }
    return 0;
}
