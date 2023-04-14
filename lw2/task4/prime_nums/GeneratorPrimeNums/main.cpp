#include <iostream>
#include <iterator>
#include <optional>
#include <string>
#include "GeneratorPrimeNums.h"

const int MAX_NUM = 100000000;
const std::string ERROR_MSG_INVALID_NUM = "Incorrect number is entered";
const int QUANTITY_ARGS = 2;
const std::string ERROR_MSG_ARGS = "Incorrect quantity of arguments is entered";

int ConvertStringToInt(const std::string& textNumber)
{
    try
    {
        int num = std::stoi(textNumber);
        return num;
    }
    catch (std::invalid_argument const& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
};

struct Args
{
    int upperBound;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != QUANTITY_ARGS)
    {
        std::cout << ERROR_MSG_ARGS << std::endl;
        return std::nullopt;
    }

    Args args;
    args.upperBound = ConvertStringToInt(argv[1]);

    return args;
};

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    int upperBound = args->upperBound;

    if (upperBound <= MAX_NUM)
    {
        std::set<int> primeNums = GeneratePrimeNumbersSet(upperBound);
        std::copy(primeNums.begin(), primeNums.end(), std::ostream_iterator<int>(std::cout, "\n"));
    }
    else
    {
        std::cout << ERROR_MSG_INVALID_NUM << std::endl;
    }

    return 0;
}