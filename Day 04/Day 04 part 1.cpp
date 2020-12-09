#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

constexpr std::uint_fast8_t mask0{ 1 << 0 }; // 0000 0001 byr (Birth Year)
constexpr std::uint_fast8_t mask1{ 1 << 1 }; // 0000 0010 iyr (Issue Year)
constexpr std::uint_fast8_t mask2{ 1 << 2 }; // 0000 0100 eyr (Expiration Year)
constexpr std::uint_fast8_t mask3{ 1 << 3 }; // 0000 1000 hgt (Height)
constexpr std::uint_fast8_t mask4{ 1 << 4 }; // 0001 0000 hcl (Hair Color)
constexpr std::uint_fast8_t mask5{ 1 << 5 }; // 0010 0000 ecl (Eye Color)
constexpr std::uint_fast8_t mask6{ 1 << 6 }; // 0100 0000 pid (Passport ID)
constexpr std::uint_fast8_t mask7{ 1 << 7 }; // 1000 0000 cid (Country ID)

int main()
{
    std::vector<std::string> data;
    std::ifstream inputFile("Day 04 input.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (getline (inputFile, s))
        {
            data.push_back(s);
        }
        inputFile.close();
    }
    int answer{0};
    std::bitset<8> bits{0};
    for (auto &element : data)
    {
        for (int i{0}; i<element.size(); ++i)
        {
            if (element.at(i) == ':')
            {
                std::string str {element.substr(i-3,3)};
                if (str=="byr")
                    bits |= mask0;
                if (str=="iyr")
                    bits |= mask1;
                if (str=="eyr")
                    bits |= mask2;
                if (str=="hgt")
                    bits |= mask3;
                if (str=="hcl")
                    bits |= mask4;
                if (str=="ecl")
                    bits |= mask5;
                if (str=="pid")
                    bits |= mask6;
                if (str=="cid")
                    bits |= mask7;
            }
        }
        if (element == "")
        {
            if ((bits == 0b01111111) || (bits == 0b11111111))
                ++answer;
            bits = 0;
            continue;
        }
    }
    std::cout << "The answer is: " << answer << '\n';
    return 0;
}
