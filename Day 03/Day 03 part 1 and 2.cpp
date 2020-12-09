#include <iostream>     //std::cout
#include <fstream>      //std::ifstream
#include <string>       //std::string
#include <vector>       //std::vector

// Day 3 part 1 - check right 3 and down 1 for given input
// Day 3 part 2 - check right 1 and down 1, 
//                check right 3 and down 1, 
//                check right 5 and down 1, 
//                check right 7 and down 1, 
//                check right 1 and down 2 for given input.

int treesHit (const std::vector<std::string> &Forest, int right, int down=1)
{
    int answer{0}, position{0}, stringLength{Forest.at(0).size()};
    for (int i{0}; i<Forest.size(); i+=down)
    {
        if (Forest.at(i).at(position)=='#')
            ++answer;
        position+=right;
        position = position % stringLength ;
    }
    std::cout << "For path right:" << right << " and down:" << down << " the answer is:" << answer << '\n';
    return answer;
}

int main()
{
    std::vector<std::string> Forest;
    std::ifstream inputFile("Day 03 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (inputFile >> s)
        {
            Forest.push_back(s);
        }
        inputFile.close();
    }
    int answer{1};
    answer*= treesHit (Forest, 1);
    answer*= treesHit (Forest, 3);
    answer*= treesHit (Forest, 5);
    answer*= treesHit (Forest, 7);
    answer*= treesHit (Forest, 1, 2);
    std::cout << "Every answer multiplied: " << answer <<'\n';
    return 0;
}
