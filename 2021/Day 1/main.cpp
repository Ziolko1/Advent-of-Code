#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<uint32_t> parsedInput (std::string filename)
{
    uint32_t buffer;
    std::vector<uint32_t> output;
    std::ifstream input (filename);
    while (input >> buffer)
    {
        output.push_back(buffer);
    }
    input.close();
    return output;
}
uint32_t task1 (const std::vector<uint32_t>& data)
{
    uint32_t counter{0};
    for (uint32_t i{1}; i<data.size(); ++i)
    {
        if (data.at(i) > data.at(i-1))
            ++counter;
    }
    return counter;
}
uint32_t task2 (const std::vector<uint32_t>& data)
{
    uint32_t counter{0}, sum1{9999999}, sum2{0};
    for (uint32_t i{2}; i<data.size(); ++i)
    {
        sum2 = sum1;
        sum1 = data.at(i-2)+data.at(i-1)+data.at(i);
        if (sum1 > sum2)
            ++counter;
    }
    return counter;
}
int main()
{
    std::vector<uint32_t> v(parsedInput("input.txt"));
    std::cout << "Answer to 1. half: " << task1(v) << '\n';
    std::cout << "Answer to 2. half: " << task2(v) << '\n';
    return 0;
}
