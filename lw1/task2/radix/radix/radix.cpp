#include <iostream>
#include <optional>

using namespace std;

struct Args
{
    string sourceNotation;
    string destinationNotation;
    string value;
};

const int NUM_OF_ARGS = 4;
const string ERROR_MSG_NUM_OF_ARGS = "Incorrect number of arguments";

optional<Args> GetArgs(int argc, char * argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        cout << ERROR_MSG_NUM_OF_ARGS << endl;
        return nullopt;
    };

    Args args;
    args.sourceNotation = argv[1];
    args.destinationNotation = argv[2];
    args.value = argv[3];

    return args;
};

int main(int argc, char * argv[])
{
    auto args = GetArgs(argc, argv);

    if (!args)
        return 1;

    bool wasError = false;
    string sourceNotation = args->sourceNotation;
    string destinationNotation = args->destinationNotation;

}