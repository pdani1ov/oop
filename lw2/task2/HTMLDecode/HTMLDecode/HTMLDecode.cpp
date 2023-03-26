#include <iostream>
#include <string>
#include <map>

using namespace std;

const map<string, char> HTML_ENTITY_MAP = {
    {"&quot;", '\"'},
    {"&apos;", '\''},
    {"&lt;", '<'},
    {"&qt;", '>'},
    {"&amp;", '&'}
};
const char AMP = '&';

void CheckSubtring(string const& html, unsigned& pos, char& tmpCh)
{
    for (auto& infoEntity : HTML_ENTITY_MAP)
    {
        if (html.substr(pos, infoEntity.first.length()) == infoEntity.first)
        {
            tmpCh = infoEntity.second;
            pos += infoEntity.first.length() - 1;
            break;
        }
    }
};

string HTMLDecode(string const& html)
{
    string decodedStr;

    for (unsigned i = 0; i < html.length(); i++)
    {
        if (html[i] == AMP)
        {
            char tmpCh = AMP;
            CheckSubtring(html, i, tmpCh);
            decodedStr += tmpCh;
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