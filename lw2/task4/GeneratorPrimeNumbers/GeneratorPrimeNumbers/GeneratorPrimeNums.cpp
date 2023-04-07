#include "GeneratorPrimeNums.h"

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNums;

    if (upperBound < 2)
    {
        return primeNums;
    }

    primeNums.insert(2);

    std::vector<int> sieve(upperBound + 1, true);

    for (int i = 4; i < upperBound; i += 2)
    {
        sieve[i] = false;
    }

    int sqrtUpperBound = sqrt(upperBound);

    for (int i = 3; i <= upperBound; i += 2)
    {
        if (sieve[i])
        {
            primeNums.insert(i);

            if (i <= sqrtUpperBound)
            {
                for (int j = 3 * i; j <= upperBound; j += 2 * i)
                {
                    sieve[j] = false;
                }
            }
        }
    }

    return primeNums;
}