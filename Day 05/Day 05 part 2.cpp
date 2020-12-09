#include <iostream>     //std::cout
#include <fstream>      //std::ifstream
#include <string>       //std::string
#include <vector>       //std::vector
#include <algorithm>    //std::sort
#include <chrono>

//This one got some extra bits - I thought about 2 diffrent approaches 
//And decided to time them. Because program got both very fast, I did 1 million runs each
//First method results:  test 1 -> 8.48448s test 2 -> 8.49449 test 3 -> 8.49349, avarage 8.49082
//Second method results: test 1 -> 8.50049s test 2 -> 8.46148 test 3 -> 8.46348, avarage 8.47515
//Results are too close to say anything for certain (about 0.2%), but I left them in.

int evaluateSeatID (const std::string &input)
{
    int row{0}, column{0};
    for (const char &a : input)
    {
        if (a == 'F')
            row = (row << 1)+0;
        if (a == 'B')
            row = (row << 1)+1;
        if (a == 'L')
            column = (column << 1)+0;
        if (a == 'R')
            column = (column << 1)+1;
    }
    return ((8*row)+column);
}

int main()
{
    bool test1{0}, test2{1};
    int testCases {1000000};
    std::vector <int> seatIDs;
    std::ifstream inputFile ("Day 05 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (inputFile >> s)
        {
            seatIDs.push_back(evaluateSeatID(s));
        }
        inputFile.close();
    }
    std::sort (seatIDs.begin(), seatIDs.end());

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
    if (test1)
    {   
        for (int xyz{0}; xyz<testCases; ++xyz)
        {
            int i{seatIDs.at(0)};
            for (auto &element : seatIDs)
            {
                if (element != i)
                {
                    std::cout << "Expected (answer): " << i << " Got: " << element << '\n';
                    i=element;
                }
                ++i;
            }
        }
    }

    if (test2)
    {   
        for (int xyz{0}; xyz<testCases; ++xyz)
        {
            int sumHypothetical{(seatIDs.front()+seatIDs.back())*(seatIDs.size()+1)/2}, sumTrue{0};
            for (auto &element : seatIDs)
            {
                sumTrue+=element;
            }
        }
        std::cout << "Missing element is: " << sumHypothetical-sumTrue <<'\n';
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Computation finish time: " << elapsed_seconds.count() << "s\n";
    return 0;
}
