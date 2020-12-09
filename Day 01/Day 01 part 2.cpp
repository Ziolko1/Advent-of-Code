#include <iostream>     //std::cout
#include <algorithm>    //std::sort
#include <vector>       //std::vector for number list
#include <fstream>      //std::ifstream

int main()
{
    std::vector <int> Numbers;
    std::ifstream inputFile("Day 01 input.txt");
    if(inputFile.is_open())
    {
        int buffer{0};
        while (inputFile >> buffer)
        {
            Numbers.push_back(buffer);
        }
        inputFile.close();
    }
    std::sort(Numbers.begin(), Numbers.end());
    /*for (int &e : Numbers)
        std::cout << e << '\n';*/

    for (std::vector<int>::iterator first {Numbers.begin()}; first!= Numbers.end(); ++first)
    {
        std::vector<int>::iterator second  {first+1};
        std::vector<int>::reverse_iterator third {Numbers.rbegin()};

        while ((*second)<(*third))
        {
            if (((*first)+(*second)+(*third)) == 2020)
            {
                std::cout << (*first) << '+' << (*second) << '+' << (*third)
                          << '=' <<((*first)+(*second)+(*third)) << '\n'
                          << (*first) << '*' << (*second) << '*' << (*third)
                          << '=' <<((*first)*(*second)*(*third)) << '\n';
                ++second;
                ++third;
                break;
            }
            if (((*first)+(*second)+(*third)) < 2020)
                ++second;
            if (((*first)+(*second)+(*third)) > 2020)
                ++third;
        }
    }
    return 0;
}
