#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using TYPE1 = int;
using TYPE2 = uint64_t;

template <typename T>
void printVector (const std::vector<T>& data)
{
    for (const T &entry : data)
    {
        std::cout << entry << '\n';
    }
    std::cout << '\n';
}

std::vector<TYPE2> parsedInput (std::string filename)
{
    int buffer;
    char garbage;
    std::vector<TYPE2> output (10, 0);
    std::ifstream input (filename);
    while (input >> buffer)
    {
        output.at(buffer)++;
        input >> garbage;
    }
    input.close();
    return output;
}

void progressADay(std::vector<TYPE2>& data)
{
    TYPE2 buffer = data.at(0);
    for (int i{0}; i<8; ++i)
    {
        data.at(i) = data.at(i+1);
    }
    data.at(8) = buffer;
    data.at(6) += buffer;
}
TYPE2 countFish(const std::vector<TYPE2>& data)
{
    TYPE2 sum{0};
    for (const TYPE2& entry : data)
    {
        sum+= entry;
    }
    return sum;
}

TYPE2 task (std::vector<TYPE2> data, int days)
{
    for (int i{0}; i<days; ++i)
    {
        progressADay(data);
        if (i == 79 || i == 255)
        {
            std::cout << "After day: " << i << " there are: " << countFish(data) << '\n';
        }
    }
    return countFish(data);
}
int main()
{
    std::vector<TYPE2> v(parsedInput("input.txt"));
    std::cout << "Answer to 1. half: " << task(v, 80) << '\n';
    std::cout << "Answer to 2. half: " << task(v, 256) << '\n';
    return 0;
}
