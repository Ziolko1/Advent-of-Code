#include <iostream>     //std::cout
#include <fstream>      //std::ifstream & std::ofstream
#include <vector>       //std::vector
#include <string>       //std::string
#include <utility>      //std::pair
#include <sstream>      //std::sstream
#include <unordered_map>//std::unordered_map

using myMap = std::unordered_map <std::string, std::vector <std::pair <int_least64_t, std::string> > >;
using myPair = std::pair<std::string, std::vector <std::pair <int_least64_t, std::string> > >;

std::string createKey (const std::string &data)
{
    return std::string {data.substr(0,(data.find("contain")-6))};
}

std::vector <std::pair <int_least64_t,std::string> > createValue (const std::string &data)
{
    std::vector <std::pair <int_least64_t,std::string> > answer;
    std::stringstream s{data.substr((data.find("contain")+8))};
    std::string s1, s2, garbage;
    int_least64_t value;
    while (s >> value >> s1 >> s2 >> garbage)
    {
        s1+=' ';
        s1+=s2;
        answer.push_back(make_pair(value, s1));
    }
    return answer;
}

void print (const myMap& dataSet)
{
    for (const myPair &p: dataSet)
    {
        std::cout << p.first << ':';
        for (const std::pair <int_least64_t, std::string> &element : p.second)
        {
            std::cout << element.first << ' ' << element.second << ' ';
        }
        std::cout << '\n';
    }
}

int_least64_t evaluate(std::string& checking, myMap& dataSet)
{
    int_least64_t total{1};
    std::vector <std::pair <int_least64_t,std::string> > vData{dataSet.at(checking)};
    if (vData.size()==0)
        return total;
    for (std::pair<int_least64_t, std::string> &element : vData)
    {
        if (element.second == "total")
            return element.first;
    }
    for (std::pair<int_least64_t, std::string> &element : vData)
    {
        total+=element.first*evaluate(element.second, dataSet);
    }

    dataSet.at(checking).push_back(std::make_pair(total,"total"));
    return total;
}

int main()
{
    myMap dataSet;
    std::ifstream inputFile ("BAGS.txt");
    if(inputFile.is_open())
    {
        std::string s;
        while (getline (inputFile, s))
        {
            dataSet.emplace(createKey(s),createValue(s));
        }
        inputFile.close();
    }
    std::ofstream outputFile ("output.txt");
    for (auto &element : dataSet)
    {
        std::string lookingFor{element.first};
        outputFile << "Evaluated " << lookingFor << " to " << evaluate(lookingFor, dataSet) << '\n';
    }
    return 0;
}
