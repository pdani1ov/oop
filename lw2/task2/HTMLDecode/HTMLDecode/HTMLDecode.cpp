#include <iostream>
#include <string>
#include <map>

using namespace std;

const map<string, string> DICTIONARY_OF_ENTITY = {
    {"&quot;", "\""},
    {"&apos;", "\'"},
    {"&lt;", "<"},
    {"&qt;", ">"},
    {"&amp;", "&"}
};

string HTMLDecode(string const& html)
{
    string decodedStr;

    for (int i = 0; i < html.length(); i++)
    {
        if (html[i] == '&')
        {
            string tmpStr = "&";
            for (auto& infoEntity : DICTIONARY_OF_ENTITY)
            {
                if (html.substr(i, infoEntity.first.length()) == infoEntity.first)
                {
                    tmpStr = infoEntity.second;
                    i += infoEntity.first.length() - 1;
                    break;
                }
            }
            decodedStr += tmpStr;
        }
        else
        {
            decodedStr += html[i];
        }
    }

    return decodedStr;
};

int main()
{
    string str;

    while (getline(cin, str))
    {
        cout << HTMLDecode(str) << endl;
    }
}