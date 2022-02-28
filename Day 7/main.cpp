#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using TYPE2 = int32_t;

template <typename T>
void printVector (const std::vector<T>& data)
{
    for (const T &entry : data)
    {
        std::cout << entry << '\n';
    }
    std::cout << '\n';
}

int32_t abs(int32_t a)
{
    return a > 0 ? a : -a;
}
int32_t sumTo(int32_t a)
{
    return ((1+a)*a)/2;
}
std::vector<TYPE2> parsedInput (std::string filename)
{
    char garbage;
    TYPE2 buffer;
    std::vector<TYPE2> output;
    std::ifstream input (filename);
    while (input >> buffer)
    {
        output.push_back(buffer);
        input >> garbage;
    }
    input.close();
    sort(output.begin(), output.end());
    return output;
}
TYPE2 task1 (const std::vector<TYPE2>& data)
{
    TYPE2 fuel{0}, best_fuel{99'999'999};
    for (TYPE2 i {data.at(0)}; i < data.at(data.size()-1); ++i)
    {
        for (const TYPE2 &entry : data)
        {
            fuel += abs(i - entry);
        }
        if (fuel < best_fuel)
        {
            best_fuel = fuel;
            std::cout << "New best: " << fuel << " Target: " << i << '\n';
        }
        fuel = 0;
    }
    return best_fuel;
}
TYPE2 task2 (const std::vector<TYPE2>& data)
{
    TYPE2 fuel{0}, best_fuel{99'999'999};
    for (TYPE2 i {data.at(0)}; i < data.at(data.size()-1); ++i)
    {
        for (const TYPE2 &entry : data)
        {
            fuel += sumTo(abs(i - entry));
        }
        if (fuel < best_fuel)
        {
            best_fuel = fuel;
            std::cout << "New best: " << fuel << " Target: " << i << '\n';
        }
        fuel = 0;
    }
    return best_fuel;
}
//IMPLEMENT THIS SOMEHOW?
int32_t binaryLikeSearch (const std::vector <TYPE2>& data, int32_t l, int32_t r, int32_t best)
{
    if (l <= r)
    {
        int mid = (l + r)/2;
        if (arr[mid] == num)
        {
            return mid;
        }
        if (arr[mid] > num)
        {
            return binarySearch(arr, p, mid-1, num);
        }
        if (arr[mid] < num)
        {
            return binarySearch(arr, mid+1, r, num);
        }
    }
    return -1;
}

int main()
{
    std::vector<TYPE2> v(parsedInput("input.txt"));
    std::cout << "Answer to 1. half: " << task1(v) << '\n';
    std::cout << "Answer to 2. half: " << task2(v) << '\n';
    return 0;
}

