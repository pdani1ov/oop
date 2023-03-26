#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

const std::string ERROR_MSG_INCORRECT = "Incorrect data entered";

bool ParseNums(std::istream& inputFile, std::vector<double>& nums)
{
    double num;

    while ((inputFile >> num) && !inputFile.eof())
    {
        nums.push_back(round(num * 1000) / 1000);
    }

    if (nums.size() == 0)
    {
        return false;
    }

    return true;
};

std::vector<double> MultiplyMinElement(std::vector<double>& nums)
{
    double min = *min_element(nums.begin(), nums.end());

    std::vector<double> result;
    result.resize(nums.size());

    std::transform(nums.begin(), nums.end(), result.begin(), [min](double& num)
        {
            return num = round(num * min * 1000) / 1000;
        });

    return result;
};

void PrintNums(std::vector<double> const& nums)
{
    for_each(nums.cbegin(), nums.cend(), [](double num)
        {
            std::cout << num << std::endl;
        });
};

int main()
{
    std::vector<double> nums;

    if (!ParseNums(std::cin, nums))
    {
        std::cout << ERROR_MSG_INCORRECT << std::endl;
        return 1;
    }

    MultiplyMinElement(nums);

    sort(nums.begin(), nums.end());

    PrintNums(nums);

    return 0;
}
