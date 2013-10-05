#ifndef ARGUMENTPARSING_H
#define ARGUMENTPARSING_H


#include <iostream>
#include <sstream>
#include <cstring>
#include <map>


class ArgumentParsing
{
public:
    ArgumentParsing(int minArgumentNumber);
    ~ArgumentParsing();

    virtual bool Parse(int argc, char** argv);

    float LookupFloatType(std::string entry);
    std::string LookupStringType(std::string entry);
private:
    int m_minArgumentNumber;
    std::map<std::string, float> m_fFloatTypeInputs;
    std::map<std::string, std::string> m_StringTypeInputs;
};


#endif // !ARGUMENTPARCING_H
