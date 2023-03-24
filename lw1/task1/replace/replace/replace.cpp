#include <optional>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Args
{
    string inputFileName, outputFileName, searchString, replaceString;
};

const int NUM_OF_ARGS = 5;
const string ERROR_MSG_NUM_OF_ARGS = "Incorrect number of arguments";
const string ERROR_MSG_INPUT_FILE = "Input file is not found";
const string ERROR_MSG_OUTPUT_FILE = "Input file is not found";

optional<Args> GetArgs(int argc, char* argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        cout << ERROR_MSG_NUM_OF_ARGS << endl;
        return nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];

    return args;
};

string ReplaceInStr(const string& search, const string& replace, string& current)
{
    string newStr = current;
    int pos = current.find(search);

    while (pos != -1)
    {
        newStr.replace(pos, search.length(), replace);
        pos = newStr.find(search, pos + replace.length());
    }

    return newStr;
};

void Replace(ifstream& input, ofstream& output, const string& search, const string& replace)
{
    string str;
    while (getline(input, str))
    {
        output << ReplaceInStr(search, replace, str) << endl;
    }
};

int main(int argc, char* argv[])
{
    auto args = GetArgs(argc, argv);

    if (!args)
        return 1;

    ifstream input(args->inputFileName);

    if (!input.is_open())
    {
        cout << ERROR_MSG_INPUT_FILE << endl;
        return 1;
    }

    ofstream output(args->outputFileName);

    if (!input.is_open())
    {
        cout << ERROR_MSG_OUTPUT_FILE << endl;
        return 1;
    }

    string searchString = args->searchString;
    string replaceString = args->replaceString;

    Replace(input, output, searchString, replaceString);

    if (!output.flush())
    {
        cout << "Failed to save data on disk" << endl;
        return 1;
    }

    return 0;
}