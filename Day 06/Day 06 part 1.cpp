#include <iostream>     //std::cout
#include <fstream>      //std::ifstream
#include <string>       //std::string
#include <vector>       //std::vector
#include <array>        //std::array

int checkQuestionaries(std::string &data)
{
    int finalAnswer{0};
    std::array<int, 26> answers{0};
    for (char &c : data)
    {
        ++answers.at(c-'a');
    }
    for (const int &i : answers)
    {
        if (i!=0)
            ++finalAnswer;
    }
    return finalAnswer;
}

int main()
{
    int answer {0};
    std::string questionAnswers;
    std::ifstream inputFile("Day 06 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (getline (inputFile, s))
        {
            if (s.empty())
            {
                answer+=checkQuestionaries(questionAnswers);
                questionAnswers.clear();
            }
            else
            {
                questionAnswers+=s;
            }
        }
        answer+=checkQuestionaries(questionAnswers);
        inputFile.close();
    }
    std::cout << "Answer: "<< answer << '\n';
    return 0;
}
