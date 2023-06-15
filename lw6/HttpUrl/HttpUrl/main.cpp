#include <iostream>
#include "HttpUrl.h"

int main()
{
    std::string strUrl;
	getline(std::cin, strUrl);
	while (!std::cin.eof())
    {
		try
		{
			CHttpUrl url(strUrl);
			std::cout << url.GetURL() << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		getline(std::cin, strUrl);
    }
}
