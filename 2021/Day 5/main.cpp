#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const bool DEBUG {0};

template <typename T>
void printVector (const std::vector<T>& data)
{
    for (const T &entry : data)
    {
        std::cout << entry << '\n';
    }
    std::cout << '\n';
}

class Point
{
    int m_x, m_y;
public:
    Point(int x, int y) : m_x {x}, m_y {y} {}
    int getX() const        {return m_x;}
    int getY() const        {return m_y;}
    friend bool operator> (const Point& p1, const Point& p2);
    friend std::ostream& operator<< (std::ostream& out, const Point& p);
};
class Line
{
    Point end1, end2;
public:
    Line(int a, int b, int c, int d) : end1 {a, b}, end2 {c,d} {}
    Point getEnd1() const   {return end1;}
    Point getEnd2() const   {return end2;}
    friend std::ostream& operator<< (std::ostream& out, const Line& l);
};

std::ostream& operator<< (std::ostream& out, const Point& p)
{
    out << '(' << p.m_x << ',' << p.m_y << ')';
    return out;
}
std::ostream& operator<< (std::ostream& out, const Line& l)
{
    out << l.end1 << " -> " << l.end2;
    return out;
}
bool operator> (const Point& p1, const Point& p2)
{
    return p1.m_x+p1.m_y > p2.m_x+p2.m_y ? true : false;
}

std::vector<Line> parsedInput (std::string filename)
{
    int a, b, c, d;
    char garbage;
    std::vector<Line> output;
    std::ifstream input (filename);
    while (input >> a >> garbage >> b >> garbage >> garbage >> c >> garbage >> d)
    {
        output.emplace_back(a, b, c, d);
    }
    input.close();
    return output;
}
std::vector<Line> filter (const std::vector<Line>& input)
{
    std::vector<Line> HAV;
    for (const Line& l : input)
    {
        if (l.getEnd1().getX() == l.getEnd2().getX() || l.getEnd1().getY() == l.getEnd2().getY())
            HAV.push_back(l);
    }
    return HAV;
}
uint32_t pos (const Point& p, int dx, int dy)
{
    if (DEBUG)
    {
        std::cout << "Marking point (" << (p.getX() - dx) << ',' << (p.getY() - dy) << ")\n";
        getchar();
    }
    return (p.getX() - dx) + (p.getY() - dy) * 1000;
}

int task (const std::vector<Line>& data)
{
    int answer{0}, dx{0}, dy{0};
    std::vector<char> map(1'000'000, 0);
    for (const Line& l : data)
    {
        dx = l.getEnd1().getX() - l.getEnd2().getX();
        dy = l.getEnd1().getY() - l.getEnd2().getY();
        map.at(pos(l.getEnd1(), dx, dy))++;
        while (dx != 0 || dy != 0)
        {
            if (dx > 0) --dx;
            if (dx < 0) ++dx;
            if (dy > 0) --dy;
            if (dy < 0) ++dy;
            map.at(pos(l.getEnd1(), dx, dy))++;
        }
    }
    getchar();
    for (int i{0}; i<map.size(); ++i)
        if (map.at(i) >= 2)
            ++answer;
    return answer;
}
int main()
{
    std::vector<Line> v(parsedInput("input.txt"));
    std::vector<Line> HAV (filter (v));     //HAV - Horizontal And Vertical (only)
    std::cout << "Answer to 1. half: " << task(HAV) << '\n';
    std::cout << "Answer to 2. half: " << task(v) << '\n';
    return 0;
}
