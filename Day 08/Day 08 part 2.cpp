#include <iostream>   //std::cout
#include <fstream>    //std::ifstream
#include <string>     //std::string 
#include <vector>     //std::vector

void swapStrings (std::string &data)
{
    if (data.substr(0,3) =="nop")
    {
        data.replace(0,3,"jmp",0,3);
        return;
    }
    if (data.substr(0,3) =="jmp")
    {
        data.replace(0,3,"nop",0,3);
        return;
    }
    return;
}

int stringToInt (const std::string &data)
{
    int tempNumber{0}, multiplier{1};
    for (std::string::const_reverse_iterator it = data.rbegin(); it!=data.rend(); ++it)
    {
        tempNumber+=(*it-48)*multiplier;
        multiplier*=10;
    }
    return tempNumber;
}

int signToInt (const std::string &data)
{
    int tempNumber{stringToInt(data.substr(1))};
    if (data.at(0)=='-')
        return -tempNumber;
    else
        return tempNumber;
}

int main()
{
    std::vector <std::string> instructionSet;
    std::ifstream inputFile("Day 08 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (getline (inputFile, s))
        {
            instructionSet.push_back(s);
        }
        inputFile.close();
    }
    for (int j=0; j<instructionSet.size(); ++j)
    {
        bool looping{0};
        int accumulator{0};
        std::vector<bool> instructionDone(instructionSet.size(), 0);
        swapStrings(instructionSet.at(j));
        for (int i{0}; i<instructionSet.size(); ++i)
        {
            std::string key{instructionSet.at(i).substr(0,3)};
            int value{signToInt(instructionSet.at(i).substr(4))};

            if (instructionDone.at(i)==true)
            {
                looping=true;
                break;
            }
            else
                instructionDone.at(i)=true;
            if (key == "acc")
                accumulator += value;
            if (key == "jmp")
                i+= value-1;
        }
        if (!looping)
        {
            std::cout << "Answer: " << accumulator << " Changed: " << j;
            return 0;
        }
        swapStrings(instructionSet.at(j));
    }
    return 0;
}
