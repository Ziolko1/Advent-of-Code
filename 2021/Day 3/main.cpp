#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
        output.push_back(buffer);
    }
    input.close();
    return output;
}
uint32_t binToDec (const std::string& data)
{
    uint32_t answer {0};
    for (int i{0}; i<data.size(); ++i)
    {
        answer<<=1;
        if (data.at(i) == '1')
            ++answer;
    }
    return answer;
}
char logic (uint32_t zeroes, uint32_t ones, bool oxygen)
{   //returns what is to be deleted
    if (zeroes > ones)
    {
        if (oxygen)
            return '1';
        else
            return '0';
    }
    else
    {
        if (oxygen)
            return '0';
        else
            return '1';
    }
}
void discard (std::vector<std::string>& data, uint32_t index, char todelete)
{
    for (int i{0}; i<data.size(); ++i)
    {
        if (data.at(i).at(index) == todelete)
        {
            data.erase(data.begin()+i);
            --i;
        }
    }
}
std::string rating (const std::vector<std::string>& data, bool oxygen)
{
    std::vector <std::string> workData {data};
    for (uint32_t i{0}; i<data.at(0).size(); ++i)
    {
        uint32_t zeroes{0}, ones{0};
        for (int j{0}; j<workData.size(); ++j)
        {
            if (workData.at(j).at(i) == '1')
                ++ones;
            else
                ++zeroes;
        }
        discard (workData, i, logic(zeroes, ones, oxygen));

        if(workData.size()==1)
        {
            std::cout << "Returning: " << workData.at(0) << '\n';
            return workData.at(0);
        }
        else
            std::cout << "Set size: " << workData.size() << '\n';
    }
    std::cout << "Something went wrong!\n";
    return "Something went wrong!";
}

uint64_t task1 (const std::vector<std::string>& data)
{
    std::vector <uint32_t> ones   (data.at(0).size(), 0);
    std::vector <uint32_t> zeroes (data.at(0).size(), 0);
    for (const std::string &s : data)
    {
        for (int i{0}; i<s.size(); ++i)
        {
            if (s.at(i) == '1')
                ++ones.at(i);
            else
                ++zeroes.at(i);
        }
    }
    uint64_t gamma{0}, epsilon{0};  //gamma MOST common, epsilon LEAST common
    for (int i{0}; i<ones.size(); ++i)
    {
        gamma<<=1;
        epsilon<<=1;
        if (ones.at(i) > zeroes.at(i))
            gamma+=1;
        else
            epsilon+=1;
    }
    return gamma*epsilon;
}
uint64_t task2 (const std::vector<std::string>& data)
{
    return binToDec (rating(data, false)) * binToDec(rating(data, true));
}
int main()
{
    std::vector<std::string> v(parsedInput("input.txt"));
    std::cout << "Answer to 1. half: " << task1(v) << '\n';
    std::cout << "Answer to 2. half: " << task2(v) << '\n';
    return 0;
}


/*Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

    Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
    If you only have one number left, stop; this is the rating value for which you are searching.
    Otherwise, repeat the process, considering the next bit to the right.

The bit criteria depends on which type of rating value you want to find:

    To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
    To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.

For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

    Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.
    Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
    In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
    In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
    In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
    As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.

Then, to determine the CO2 scrubber rating value from the same example above:

    Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
    Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
    In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
    As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.

Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)*/

