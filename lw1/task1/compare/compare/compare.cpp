#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool Compare(ifstream& f1, ifstream& f2);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments" << endl;
        return 1;
    }

    ifstream f1(argv[1]);

    if (!f1.is_open())
    {
        cout << "File 1 is not found" << endl;
        return 1;
    }

    ifstream f2(argv[2]);

    if (!f2.is_open())
    {
        cout << "File 2 is not found" << endl;
        return 1;
    }

    if (Compare(f1, f2))
    {
        cout << "Files are equal" << endl;
    }
    else
    {
        cout << "Files are different" << endl;
    }
    
    return 0;
}

bool Compare(ifstream& f1, ifstream& f2)
{
    string line1, line2;
    int numberOfLine = 1;

    while (!f1.eof() || !f2.eof())
    {
        getline(f1, line1);
        getline(f2, line2);

        if (line1.compare(line2) == 0)
        {
            numberOfLine++;
        }
        else
        {
            cout << numberOfLine << endl;
            return false;
        }
    }

    return true;
}
