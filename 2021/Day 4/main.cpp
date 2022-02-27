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

class Cell
{
    int m_value;
    bool m_marked;
public:
    Cell(int value, bool mark=false) : m_value{value}, m_marked{mark} {}
    int getValue () const       {return m_value;}
    bool getMark () const       {return m_marked;}
    void setValue (int v)       {m_value = v;}
    void setMark (bool b)       {m_marked = b;}
    friend std::ostream& operator<< (std::ostream& out, const Cell& c);
};
class Bingo_Board
{
    std::vector <Cell> m_board;

public:
    Bingo_Board(int start) : m_board{start} {}
    Cell getCell(int index) const {return m_board.at(index);}
    void addCell(int value)       {m_board.emplace_back(value);}
    bool mark(int number)
    {
        for (Cell& c : m_board)
        {
            if (c.getValue() == number)
            {
                c.setMark(true);
                return true;
            }
        }
    return false;
    }
    bool checkWin()
    {
        for (int i{0}; i<5; ++i)
        {
            if  (m_board.at(i*5  ).getMark()&& m_board.at(i*5+1).getMark() && m_board.at(i*5+2).getMark()
              && m_board.at(i*5+3).getMark()&& m_board.at(i*5+4).getMark()) //check rows
                return true;

            if  (m_board.at(i   ).getMark() && m_board.at(i+5 ).getMark() && m_board.at(i+10).getMark()
              && m_board.at(i+15).getMark() && m_board.at(i+20).getMark())  //check columns
                return true;
        }
        return false;
    }
    int sumOfUnmarked()
    {
        int answer {0};
        for (const Cell& c : m_board)
        {
            if (!c.getMark())
                answer+=c.getValue();
        }
        return answer;
    }
    friend std::ostream& operator<< (std::ostream& out, const Bingo_Board& b);
};

std::ostream& operator<< (std::ostream& out, const Bingo_Board& b)
{
    for (int i{0}; i<5; ++i)
    {
        for (int j{0}; j<5; ++j)
        {
            out << b.getCell(i*5+j) << '\t';
        }
        out << '\n';
    }
    out << '\n';
    return out;
}
std::ostream& operator<<(std::ostream& out, const Cell& c)
{
    out << c.m_value;
    c.m_marked ? out << '+' : out << '-';
    return out;
}

void parseInput (std::string filename, std::vector<int>& numbers, std::vector<Bingo_Board>& boards)
{
    int buffer;
    char garbage;
    std::ifstream input (filename);
    while (input >> buffer)
    {
        numbers.push_back(buffer);
        if (input.peek() == ',')
            input >> garbage;
        else
            break;
    }
    int counter {0};
    while (input >> buffer)
    {
        if (counter%25 == 0)
            boards.emplace_back(buffer);
        else
            boards.at(counter/25).addCell(buffer);
        ++counter;
    }
    input.close();
}
int task1 (const std::vector<int>& numbers, std::vector<Bingo_Board> boards)    //COPY BOARDS
{
    bool gameover {0}, gotMarked{0};
    for (uint32_t i{0}; i < numbers.size(); ++i)
    {
        for (Bingo_Board& b : boards)
        {
            gotMarked = b.mark(numbers.at(i));
            if (gotMarked)
            {
                gameover = b.checkWin();
                if (gameover)
                    return b.sumOfUnmarked() * numbers.at(i);
            }
        }
    }
    return -1;
}
int task2 (const std::vector<int>& numbers, std::vector<Bingo_Board> boards)    //COPY BOARDS
{
    bool gameover {0}, gotMarked{0};
    for (uint32_t i{0}; i < numbers.size(); ++i)
    {
        for (uint32_t j{0}; j < boards.size(); ++j)
        {
            gotMarked = boards.at(j).mark(numbers.at(i));
            if (gotMarked)
            {
                gameover = boards.at(j).checkWin();
                if (gameover)
                {
                    if (boards.size() > 1)
                    {
                        boards.erase(boards.begin()+j);
                        j=0;
                    }
                    else
                         return boards.at(j).sumOfUnmarked() * numbers.at(i);
                }
            }
        }
    }
    return -1;
}
int main()
{
    std::vector <int> numbers;
    std::vector <Bingo_Board> boards;
    parseInput("input.txt", numbers, boards);
    std::cout << "Answer to 1. half: " << task1(numbers, boards) << '\n';
    std::cout << "Answer to 2. half: " << task2(numbers, boards) << '\n';
    return 0;
}
