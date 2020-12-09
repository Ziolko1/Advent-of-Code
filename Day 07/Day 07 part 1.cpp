#include <iostream>   //std::cout
#include <fstream>    //std::ifstream
#include <string>     //std::string
#include <vector>     //std::vector

struct doubleString
{
    std::string sKey;
    std::vector <std::string> sValues;
    void print()
    {
        std::cout << sKey << ':';
        for (std::string &element : sValues)
        {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
};

doubleString foo(std::string &bag)
{
    unsigned int temp {2}, containPos {bag.find("contain")};
    std::string color{bag.substr(0,containPos-2)}, con{bag.substr(containPos+8)};
    std::vector <std::string> contents;
    for (unsigned int i{0}; i<con.size(); ++i)
    {
        if ((con.at(i) == '.') || (con.at(i) == ','))
        {
            if (con.at(i-1)=='s')
            {
                contents.push_back(con.substr(temp, i-temp-1));
                temp=i+4;
            }
            else
            {
                contents.push_back(con.substr(temp, i-temp));
                temp=i+4;
            }
        }
    }
    return doubleString{color, contents};
}

int main()
{
    std::vector <doubleString> bags;
    std::ifstream inputFile("Day 07 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (getline (inputFile, s))
        {
            bags.push_back(foo(s));
        }
        inputFile.close();
    }
    std::vector <std::string> input;
    input.reserve(1000);
    input.push_back("shiny gold bag");
    std::vector<std::string>::iterator it{input.begin()};

    while (it != input.end())
    {
        for (doubleString &sth : bags)
        {
            for (std::string str : sth.sValues)
            {

                if (str.find(*it)!= std::string::npos)
                {
                    int temp{0};
                    for (std::string &element : input)
                    {
                        if (element==sth.sKey)
                        {
                            break;
                        }
                        else
                        {
                            ++temp;
                        }
                    }
                    if (temp == input.size())
                    {
                        input.push_back(sth.sKey);
                    }
                }
            }
        }
        ++it;
    }
    std::cout << "Answer: " <<input.size()-1 << '\n';
    return 0;
}
