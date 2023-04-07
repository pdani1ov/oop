#include <iostream>
#include <set>
#include <vector>
#include <optional>
#include <ctime>
#include "GeneratorPrimeNums.h"

const int MAX_NUM = 100000000;
const std::string ERROR_MSG_INVALID_NUM = "Incorrect number is entered";

void PrintPrimeNums(const std::set<int> primeNums)
{
    for (auto& prime : primeNums)
    {
        std::cout << prime << std::endl;
    }
};

int main(int argc, char* argv[])
{
    int upperBound;

    while (std::cin >> upperBound)
    {
        if (upperBound <= MAX_NUM)
        {
            unsigned int timeBegin = clock();
            std::set<int> primeNums = GeneratePrimeNumbersSet(upperBound);
            unsigned int timeEnd = clock();
            //PrintPrimeNums(primeNums);
            std::cout << primeNums.size() << " " << timeEnd - timeBegin << std::endl;
        }
        else
        {
            std::cout << ERROR_MSG_INVALID_NUM << std::endl;
        }
    }

    return 0;
}