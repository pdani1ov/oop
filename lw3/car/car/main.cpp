#include <iostream>
#include <windows.h>
#include "Car.h"
#include "CarController.h"

const std::string ERROR_MSG_UNKNOWN_COMMAND = "Unknown command!";

int main()
{
    CCar car;
    CCarController remoteControl(car, std::cin, std::cout);

    while (!std::cin.eof())
    {
        if (!remoteControl.HandleCommand())
        {
            std::cout << ERROR_MSG_UNKNOWN_COMMAND << std::endl;
        }
    }

    return 0;
}