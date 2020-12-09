#include <iostream>     //std::cout
#include <fstream>      //std::ifstream
#include <string>       //std::string
#include <vector>       //std::vector
#include <array>        //std::array

int checkQuestionaries(std::vector <std::string> &data)
{
    int finalAnswer{0};
    std::vector <std::array <bool, 26> > answers;
    for (std::string &element : data)
    {
        std::array <bool, 26> bArray {0};
        for (char &letter : element)
        {
            bArray.at(letter-'a')=1;
        }
        answers.push_back(bArray);
    }
    std::array <bool,26> testCase;
    for (bool &b : testCase)
        b=1;
    for (std::array <bool, 26> &abc : answers)
    {
        for (int i{0}; i<abc.size(); ++i)
            testCase.at(i)=testCase.at(i)&abc.at(i);
    }
    for (bool &b : testCase)
    {
        if (b) ++finalAnswer;
    }
    return finalAnswer;
}

int main()
{
    int answer {0};
    std::vector <std::string> groupAnswers;
    std::ifstream inputFile("Day 06 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (getline (inputFile, s))
        {
            if (s.empty())
            {
                answer+=checkQuestionaries(groupAnswers);
                groupAnswers.clear();
            }
            else
            {
                groupAnswers.push_back(s);
            }
        }
        answer+=checkQuestionaries(groupAnswers);
        inputFile.close();
    }
    std::cout << "Answer: "<< answer << '\n';
    return 0;
}
