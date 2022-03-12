#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// Seven segment display:
// Two segments     -> 1
// Three segments   -> 7
// Four segments    -> 4
// Five segments    -> 2, 3, 5
// Six segments     -> 0, 6, 9
// Seven segments   -> 8
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
            l.push_back(buffer);
        }
        input >> garbage;
        for (int i{0}; i<4; ++i)
        {
            input >> buffer;
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
int32_t task2 (const std::vector<LineOfData>& data)
{
    int32_t answer;
    return answer;
}
void analyzeData (const std::vector<LineOfData>& data)
{
    for (int i{0}; i<data.size(); ++i)
    {
        std::vector<int32_t> d (10, 0);
        for (int j{0}; j<data.at(i).getLeft().size(); ++j)
        {
            ++d.at(data.at(i).getLeft().at(j).size());
        }
        for (int j{0}; j<data.at(i).getRight().size(); ++j)
        {
            ++d.at(data.at(i).getRight().at(j).size());
        }
        for (int j{2}; j<8; ++j)
        {
            if (!d.at(j))
                std::cout << i << ' ' << j << ':' << d.at(j) << '\n';

        }

    }
}
int main()
{
    std::vector<LineOfData> v(parsedInput("input.txt"));
    analyzeData(v);
    std::cout << "Answer to 1. half: " << task1(v) << '\n';
    std::cout << "Answer to 2. half: " << task2(v) << '\n';
    return 0;
}