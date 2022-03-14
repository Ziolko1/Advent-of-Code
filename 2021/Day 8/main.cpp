#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>    //Sort
// Seven segment display:
// Two segments     -> 1
// Three segments   -> 7
// Four segments    -> 4
// Five segments    -> 2, 3, 5
// Six segments     -> 0, 6, 9
// Seven segments   -> 8
// There is no data set without digits 1, 4, 7 or 8
/* defabc gcb dbafcg gc gcbed fbecgd begfdac fcbde cfge debag
    cg      -> 1                 => upper right and lower right
    gcb     -> 7, - gc    -> b   => b is the top part of the display
    cfge    -> 4, - gc    -> fe  => upper left, and middle pieces
    begfdac -> 8, - cfgeb -> ad  => lower left and down pieces

*/
class LineOfData
{
    std::vector <std::string> m_left;
    std::vector <std::string> m_right;
public:
    LineOfData(std::vector <std::string>& l, std::vector <std::string>& r) : m_left(l), m_right (r) {}
    const std::vector <std::string>& getLeft() const
    {
        return m_left;
    }
    const std::vector <std::string>& getRight() const
    {
        return m_right;
    }
    friend std::ostream& operator<< (std::ostream& out, const LineOfData& lod);
};

std::ostream& operator<< (std::ostream& out, const LineOfData& lod)
{
    for (const std::string& data : lod.getLeft())
    {
        out << data << ' ';
    }
    out << "| ";
    for (const std::string& data : lod.getRight())
    {
        out << data << ' ';
    }
    return out;
}
std::vector<LineOfData> parsedInput (std::string filename)
{
    char garbage;
    std::string buffer;
    std::vector <std::string> l;
    std::vector <std::string> r;
    std::vector<LineOfData> output;
    std::ifstream input (filename);
    while (input.peek() != EOF)
    {
        l.clear();
        r.clear();
        for (int i{0}; i<10; ++i)
        {
            input >> buffer;
            std::sort(buffer.begin(), buffer.end());
            l.push_back(buffer);
        }
        input >> garbage;
        for (int i{0}; i<4; ++i)
        {
            input >> buffer;
            std::sort(buffer.begin(), buffer.end());
            r.push_back(buffer);
        }
        output.emplace_back(l,r);
    }
    input.close();
    return output;
}
int32_t task1 (const std::vector<LineOfData>& data)
{
    int32_t answer{0}, buffer{0};
    std::vector<int32_t> correctAnswers {2,3,4,7};
    for (const LineOfData& r : data)
    {
        for (const std::string& s : r.getRight())
        {
            buffer = s.size();
            for (const int32_t& correctAnswer : correctAnswers)
            {
                if (buffer == correctAnswer)
                {
                    ++answer;
                    break;
                }
            }
        }
    }
    return answer;
}
std::string intersection(const std::string& a, const std::string& b)
{
    std::string out;
    for (const char letter_a : a)
    {
        for (const char letter_b : b)
        {
            if (letter_a == letter_b)
            {
                out += letter_a;
                break;
            }
        }
    }
    return out;
}

std::vector <std::string> formatData(const LineOfData& lod)
{
    std::vector<std::string> workdata;
    for (const std::string& x : lod.getLeft())
        workdata.emplace_back(x);
    for (const std::string& x : lod.getRight())
        workdata.emplace_back(x);
    return workdata;
}

std::vector<std::string> decipherData (const std::vector<std::string>& data)
{
    std::string zero, one, two, three, four, five, six, seven, eight, nine;
    std::vector<std::string> two_three_five;
    std::vector<std::string> zero_six_nine;
    for (const std::string& x : data)
    {
        switch (x.size())
        {
        case 2:
            one = x; break;
        case 3:
            seven = x; break;
        case 4:
            four = x; break;
        case 5:
            two_three_five.emplace_back(x); break;
        case 6:
            zero_six_nine.emplace_back(x); break;
        case 7:
            eight = x; break;
        }
    }
    for (const std::string& x : two_three_five)
    {
        if (intersection(x, one).size() == 2)
        {
             three = x;
             break;
        }
    }
    for (const std::string& x : zero_six_nine)
    {
        if (intersection(x, four).size() == 4)
        {
            nine = x;
            break;
        }
    }
    for (const std::string& x : two_three_five)
    {
        if (intersection(x, nine).size() == 4)
        {
             two = x;
             break;
        }
    }
    for (const std::string& x : two_three_five)
    {
        if ((intersection(x, two).size() == 3) && (intersection(x, three).size() == 4))
        {
             five = x;
             break;
        }
    }
    for (const std::string& x : zero_six_nine)
    {
        if ((intersection(x, one).size() == 2) && (intersection(x, nine).size() == 5))
        {
             zero = x;
             break;
        }
    }
    for (const std::string& x : zero_six_nine)
    {
        if ((intersection(x, zero).size() == 5) && (intersection(x, nine).size() == 5))
        {
             six = x;
             break;
        }
    }
    return {zero, one, two, three, four, five, six, seven, eight, nine};
}

int32_t evaluateLine (const LineOfData& lod)
{
    int32_t answer{0};
    std::vector<std::string> workdata {formatData(lod)};
    std::vector<std::string> decipheredData {decipherData(workdata)};

    for (const std::string& digit : lod.getRight())
    {
        answer*=10;
        for (int i{0}; i<10; ++i)
        {
            if (digit == decipheredData.at(i))
            {
                answer+=i;
                break;
            }
        }
    }
    return answer;
}
int32_t task2 (const std::vector<LineOfData>& data)
{
    int32_t answer{0};
    for (const LineOfData& l : data)
    {
        answer+=evaluateLine(l);
    }
    return answer;
}

int main()
{
    std::vector<LineOfData> v(parsedInput("input.txt"));
    std::cout << "Answer to 1. half: " << task1(v) << '\n';
    std::cout << "Answer to 2. half: " << task2(v) << '\n';
    return 0;
}
