#include <iostream>     //std::cout
#include <fstream>      //std::ifstream

int main()
{
    std::ifstream inputFile("Day 02 input");
    if(inputFile.is_open())
    {
        int pos1{0}, pos2{0}, answer{0};
        char garbage{'0'}, wanted{'a'};
        std::string Password;
        while (inputFile >> pos1 >> garbage >> pos2 >> wanted >> garbage >> Password)
        {
            if ((Password.at(pos1-1)==wanted)^(Password.at(pos2-1)==wanted))
              ++answer;
        }
        inputFile.close();
        std::cout << "ANSWER: " << answer;
    }
    return 0;
}
