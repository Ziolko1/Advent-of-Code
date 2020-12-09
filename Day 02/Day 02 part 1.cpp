#include <iostream>     //std::cout
#include <vector>       //std::vector
#include <fstream>      //std::ifstream

int countOccurrences(char wanted, std::string s)
{
    int answer{0};
    for (int i{0}; i<s.size(); ++i)
        {
            if (s[i]==wanted)
                ++answer;
        }
    return answer;
}

int main()
{
    std::ifstream inputFile("Day 02 input.txt");
    if(inputFile.is_open())
    {
        int atLeast{0}, atMost{0}, answer{0}, count{0};
        char garbage{'0'}, wanted{'a'};
        std::string Password;
        while (inputFile >> atLeast >> garbage >> atMost >> wanted >> garbage >> Password)
        {
            count = countOccurrences(wanted, Password);
            if ((count >= atLeast)&&(count <= atMost))
                ++answer;
        }
        inputFile.close();
        std::cout << "Answer: " << answer;
    }
    return 0;
}
