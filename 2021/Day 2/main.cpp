#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Command
{
    char m_direction;
    uint32_t m_value;
public:
    Command(char d, uint32_t v) : m_direction(d), m_value(v)
    {}
    char getDirection() const {return m_direction;}
    uint32_t getValue() const {return m_value;}
};
std::vector<Command> parsedInput (std::string filename)
{
    std::string sbuffer;
    uint32_t vbuffer;
    std::vector<Command> output;
    std::ifstream input (filename);
    while (input >> sbuffer >> vbuffer)
    {
        output.emplace_back(sbuffer.at(0), vbuffer);
    }
    input.close();
    return output;
}
uint64_t task1 (const std::vector<Command>& data)
{
    uint64_t pos{0}, depth{0};
    for (const Command &c :data)
    {
        if (c.getDirection() == 'f')
        {
            pos+=c.getValue();
        }
        if (c.getDirection() == 'd')
        {
            depth+=c.getValue();
        }
        if (c.getDirection() == 'u')
        {
            depth-=c.getValue();
        }
    }
    return pos*depth;
}
uint64_t task2 (const std::vector<Command>& data)
{
    uint64_t pos{0}, depth{0}, aim{0};
    for (const Command &c :data)
    {
        if (c.getDirection() == 'f')
        {
            pos+=c.getValue();
            depth+=c.getValue()*aim;
        }
        if (c.getDirection() == 'd')
        {
            aim+=c.getValue();
        }
        if (c.getDirection() == 'u')
        {
            aim-=c.getValue();
        }
    }
    return pos*depth;
}
int main()
{
    std::vector<Command> v(parsedInput("input.txt"));
    std::cout << "Answer to 1. half: " << task1(v) << '\n';
    std::cout << "Answer to 2. half: " << task2(v) << '\n';
    return 0;
}
