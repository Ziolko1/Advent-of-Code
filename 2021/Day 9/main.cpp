#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>    //std::sort

template <typename T>
void printVector (const std::vector<T>& data)
{
    for (const T &entry : data)
    {
        std::cout << entry << '\n';
    }
    std::cout << '\n';
}

std::vector<std::string> parsedInput (std::string filename)
{
    std::string buffer;
    std::vector<std::string> output;
    std::ifstream input (filename);
    while (input >> buffer)
    {
        output.emplace_back(buffer);
    }
    input.close();
    return output;
}
std::string returnNeighbours(uint32_t c, uint32_t r, const std::vector<std::string>& data)
{
    std::string output;
    if (r != 0)
        output+= data.at(r-1).at(c);
    if (r != data.size()-1)
        output+= data.at(r+1).at(c);
    if (c != 0)
        output+= data.at(r).at(c-1);
    if (c != data.at(r).size()-1)
        output+= data.at(r).at(c+1);
    sort(output.begin(), output.end());
    return output;
}
uint32_t task1 (const std::vector<std::string>& data)
{
    uint32_t answer{0};
    for (uint32_t r{0}; r<data.size(); ++r)
    {
        for (uint32_t c{0}; c<data.at(r).size(); ++c)
        {
            std::string neighbours (returnNeighbours(c, r, data));
            if (data.at(r).at(c) < neighbours.at(0))
                answer+=(data.at(r).at(c) - 47);
        }
    }
    return answer;
}
struct Position
{
    uint32_t row, column;
    Position (uint32_t r, uint32_t c) : row(r), column(c) {};
};
uint32_t fillBasin (std::vector<Position>& basin, std::vector<std::string>& data)
{
    //To make sure we don't count the same basin multiple times we
    //search for all cells in a basin and then change them to 9s.
    return 1;
}
uint32_t task2 (std::vector<std::string>& data)
{
    std::vector<Position> basin;
    std::vector <uint32_t> basinSizes;
    for (uint32_t r{0}; r<data.size(); ++r)
    {
        for (uint32_t c{0}; c<data.at(r).size(); ++c)
        {
            if (data.at(r).at(c) != 9)
            {
                basin.clear();
                basin.push_back({r, c});
                basinSizes.push_back(fillBasin(basin, data));
            }
        }
    }
    sort(basinSizes.rbegin(), basinSizes.rend());
    return basinSizes.at(0) * basinSizes.at(1) * basinSizes.at(2);
}
int main()
{
    std::vector<std::string> v(parsedInput("input.txt"));
    std::cout << "Answer to 1. half: " << task1(v) << '\n';
    std::cout << "Answer to 2. half: " << task2(v) << '\n';
    return 0;
}
