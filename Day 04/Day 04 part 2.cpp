#include <iostream>     //std::cout
#include <fstream>      //std::ifstream
#include <sstream>      //std::stringstream
#include <string>       //std::string
#include <vector>       //std::vector
#include <algorithm>    //std::sort, used for "print out" debugging 

// Correct answer is 137, program is outputing 138, so 1 away.
// Probably there is a mistake in parsing of hair color, I will debug it later

int stringToInt (const std::string &sNumber)
{
    int tempNumber{0}, multiplier{1};
    for (std::string::const_reverse_iterator it = sNumber.rbegin(); it!=sNumber.rend(); ++it)
    {
        tempNumber+=(*it-48)*multiplier;
        multiplier*=10;
    }
    return tempNumber;
}

bool isInRange(int target, int lower, int higher)
{
    if ((target >= lower) && (target <=higher))
        return 1;
    else
        return 0;
}

int checkData (std::vector<std::string>& data)
{
    if (data.size()<7)
        return 0;
    int bits{0};
    for (std::string &element : data)
    {
        std::string sKey (element.substr(0,3));
        std::string sValue (element.substr(4));
        if (sKey == "byr")
        {
            if (!isInRange(stringToInt(sValue), 1920, 2002))
                return 0;
            ++bits;
        }
        if (sKey == "iyr")
        {
            if (!isInRange(stringToInt(sValue), 2010, 2020))
                return 0;
            ++bits;
        }
        if (sKey == "eyr")
        {
            if (!isInRange(stringToInt(sValue), 2020, 2030))
                return 0;
            ++bits;
        }
        if (sKey == "hgt")
        {
            if (sValue.size()<4)
                return 0;
            if (sValue.at(3)== 'm')
                return 0;
            if (sValue.at(3)== 'n')
            {
                if (!isInRange(stringToInt(sValue.substr(0,2)), 59, 76))
                    return 0;
            }
            if (sValue.at(3)=='c')
            {
                if (!isInRange(stringToInt(sValue.substr(0,3)), 150, 193))
                    return 0;
            }
            ++bits;
        }
        if (sKey == "hcl")
        {
            if (sValue.at(0) != '#')
                return 0;
            for (int i{1}; i<sValue.size(); ++i)
            {
                if(!(((sValue.at(i)>= '0') && (sValue.at(i)<= '9')) ||
                        ((sValue.at(i)>= 'a') && (sValue.at(i)<= 'f'))))
                    return 0;
            }
            ++bits;
        }
        if (sKey == "ecl")
        {
            if (!((sValue=="amb") || (sValue=="blu") || (sValue=="brn") || (sValue=="gry")
                    || (sValue=="grn") || (sValue=="hzl") || (sValue=="oth")))
                return 0;
            ++bits;
        }
        if (sKey == "pid")
        {
            if (sValue.length()!=9)
                return 0;
            for (char &c : sValue)
                if (!((c>= '0') && (c<='9')))
                    return 0;
            ++bits;
        }
    }
    if (bits < 7)
        return 0;

    std::sort (data.begin(),data.end());
    for (std::string &element : data)
        if (element.substr(0,3) != "cid")

        std::cout << element << ' ';
    std::cout << '\n';
    return 1;
}

int main()
{
    std::vector<std::string> data;
    std::ifstream inputFile("Day 04 input.txt");
    int answer {0}, calls{0};
    if(inputFile.is_open())
    {
        std::string s;
        while (getline (inputFile, s))
        {
            if (s.empty())
            {
                ++calls;
                answer+=checkData(data);
                data.clear();
            }
            else
            {
                std::stringstream buffor{s};
                s.clear();
                while (buffor >> s)
                    data.push_back(s);
            }
        }
        answer+=checkData(data);
        ++calls;
        inputFile.close();
    }
    std::cout << "The answer is: " << answer <<" Invalid passports: " << calls - answer <<'\n';
    return 0;
}
