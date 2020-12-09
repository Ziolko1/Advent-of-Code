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
    uint_least64_t invalidNo{0}, invalidNoPos{0};
    for (uint_least32_t i{25}; i<noList.size(); ++i)
    {
        bool isPossible{0};
        for (uint_least32_t j{i-25}; j<i; ++j)
        {
            for (uint_least32_t k{j+1}; k<i; ++k)
            {
                //std::cout << "Is " << (noList.at(j)) << "+" <<(noList.at(k)) << "=" << (noList.at(i)) << "?" <<((noList.at(i))==((noList.at(j))+(noList.at(k))))<<'\n';
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
            invalidNo = noList.at(i);
            invalidNoPos = i;
            break;
        }
    }
    uint_least64_t pos1{0}, pos2{0};
    for (uint_least64_t i{1}; i<invalidNoPos; ++i)
    {
        uint_least64_t sum{0};
        for (int_least64_t j{i-1}; j>=0; --j)
        {
            sum+=noList.at(j);
            if (sum == invalidNo)
            {
                std::cout << "Numbers between pos: " << j << " and pos: " << i << " add up to " << sum << '\n';
                pos1 = j;
                pos2 = i;
            }
        }
    }
    uint_least64_t lowest{1<<30}, highest{0};
    for (; pos1<pos2; ++pos1)
    {
        if (noList.at(pos1) < lowest)
            lowest = noList.at(pos1);
        if (noList.at(pos1) > highest)
            highest = noList.at(pos1);
    }
    std::cout << "Lowest no. found in range: " << lowest << "\nHighest no. found in range: " << highest << "\nSum of them is equal: " << lowest+highest;
    return 0;
}
