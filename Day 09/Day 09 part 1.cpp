#include <iostream> //std::cout
#include <fstream>  //std::ifstream
#include <vector>   //std::vector

int main()
{
    std::vector<uint_least64_t>  noList;
    std::ifstream inputFile("Day 9 input.txt");
    if(inputFile.is_open())
    {
        uint_least64_t no;
        while (inputFile >> no)
        {
            noList.push_back(no);
        }
        inputFile.close();
    }
    for (uint_least32_t i{25}; i<noList.size(); ++i)
    {
        bool isPossible{0};
        for (uint_least32_t j{i-25}; j<i; ++j)
        {
            for (uint_least32_t k{j+1}; k<i; ++k)
            {
                if ((noList.at(i))==((noList.at(j))+(noList.at(k))))
                    isPossible=true;
                if (isPossible)
                    break;
            }
            if (isPossible)
                break;
        }
        if (!isPossible)
        {
            std::cout << "Pos: " << i << " element: " << noList.at(i) << " cant be obtained!\n";
            break;
        }
    }
    return 0;
}
