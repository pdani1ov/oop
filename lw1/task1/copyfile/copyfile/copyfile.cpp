#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        return 1;
    }

    ifstream inputF(argv[1]);

    if (!inputF.is_open())
    {
        cout << "Input file is not found" << endl;
        return 1;
    }

    ofstream outputF(argv[2]);

    char ch;

    while (inputF.get(ch))
    {
        outputF << ch;
    }

    //Удостоверяемся, что все необходимые изменения внесены в файл на диске
    if (!outputF.flush()) {
        cout << "" << endl;
        return 1;
    }

    return 0;
}


