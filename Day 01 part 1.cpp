#include <iostream>   //std::cout
#include <vector>     //std::vector
#include <fstream>    //std::ifstream
#include <algorithm>  //std::sort

int main()
{
    std::vector <int> Numbers;
    Numbers.reserve(200);

    std::ifstream inputFile;
    inputFile.open ("Numbers.txt");
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

    std::vector<int>::iterator front = Numbers.begin();
    std::vector<int>::reverse_iterator back = Numbers.rbegin();

    while (front!=Numbers.end() || back!=Numbers.rend())
    {
        if (((*front)+(*back)) == 2020)
        {
            std::cout << (*front) << '+' << (*back) << '=' <<((*front)+(*back)) << '\n'
                      << (*front) << '*' << (*back) << '=' <<((*front)*(*back)) << '\n';
            break;
        }
        if (((*front)+(*back)) > 2020)
            back++;
        if (((*front)+(*back)) < 2020)
            front++;
    }
    return 0;
}
