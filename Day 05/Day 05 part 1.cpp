#include <iostream>     //std::cout
#include <fstream>      //std::ifstream
#include <string>       //std::string
#include <vector>       //std::vector

int evaluateSeatID (const std::string &input)
{
    int row{0}, column{0};
    for (const char &a : input)
    {
        if (a == 'F')
            row = (row << 1)+0;
        if (a == 'B')
            row = (row << 1)+1;
        if (a == 'L')
            column = (column << 1)+0;
        if (a == 'R')
            column = (column << 1)+1;
    }
    return ((8*row)+column);
}

int main()
{
    std::vector<std::string> passList;
    std::ifstream inputFile("Day 05 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (inputFile >> s)
        {
            passList.push_back(s);
        }
        inputFile.close();
    }
    int biggestID{0};
    for (auto &element : passList)
    {
        int buffer{0};
        buffer = evaluateSeatID (element);
        if (buffer> biggestID)
            biggestID = buffer;
    }
    std::cout << "Biggest ID is: " << biggestID << '\n';
    return 0;
}
