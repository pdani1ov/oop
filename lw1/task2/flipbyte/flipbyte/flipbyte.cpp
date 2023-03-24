#include <iostream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
    int inputByte;
};

const int NUM_OF_ARGS = 2;
const string ERROR_MSG_NUM_OF_ARGS = "Incorrect number of arguments";
const string ERROR_INCORRECT_ARGUMENT = "Input argument is not correct";
const string ERROR_INCORECT_ARGUMENT_RANGE = "This number is out of range";

int ConvertStringToInt(const string& textNumber)
{
    try
    {
        int num = stoi(textNumber);
        if ((num < 0) || (num > 255))
        {
            cout << ERROR_INCORECT_ARGUMENT_RANGE << endl;
            return -1;
        }
        else
        {
            return num;
        }
    }
    catch (invalid_argument const& e)
    {
        cout << ERROR_INCORRECT_ARGUMENT << endl << e.what() << endl;
        return -1;
    }
};

optional<Args> GetArgs(int argc, char* argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        cout << ERROR_MSG_NUM_OF_ARGS << endl;
        return nullopt;
    };

    Args args;
    args.inputByte = ConvertStringToInt(argv[1]);

    return args;
};

int ReverseByte(const int& inputByte)
{
    uint8_t byte = inputByte;

    byte = ((byte & 0b1111) << 4) | ((byte & 0b11110000) >> 4);
    byte = ((byte & 0b00110011) << 2) | ((byte & 0b11001100) >> 2);
    byte = ((byte & 0b01010101) << 1) | ((byte & 0b10101010) >> 1);

    return int(byte);
};

int main(int argc, char * argv[])
{
    auto args = GetArgs(argc, argv);

    if (!args)
    {
        return 1;
    }
        
    int inputByte = args->inputByte;

    if (inputByte == -1)
    {
        return 1;
    }

    int outputByte = ReverseByte(inputByte);

    cout << outputByte << endl;
    return 0;
}