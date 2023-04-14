#include "GeneratorPrimeNums.h"

void RemoveMultiples(std::vector<bool>& sieve, int& num, const int& upperBound)
{
    for (int j = 3 * num; j <= upperBound; j += 2 * num)
    {
        sieve[j] = false;
    }
};

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNums;

    if (upperBound < 2)
    {
        return primeNums;
    }

    primeNums.insert(2);

    std::vector<bool> sieve(upperBound + 1, true);

    for (int i = 4; i < upperBound; i += 2)
    {
        sieve[i] = false;
    }

    int sqrtUpperBound = sqrt(upperBound);

    for (int i = 3; i <= upperBound; i += 2)
    {
        if (!sieve[i])
        {
            continue;
        }

        primeNums.insert(i);

        if (i <= sqrtUpperBound)
        {
            RemoveMultiples(sieve, i, upperBound);
        }
    }

    return primeNums;
}