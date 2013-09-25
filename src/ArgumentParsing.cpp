#include "ArgumentParsing.h"


ArgumentParsing::ArgumentParsing(int minArgumentNumber)
    : m_minArgumentNumber(minArgumentNumber)
{
}


ArgumentParsing::~ArgumentParsing()
{
}


bool ArgumentParsing::Parse(int argc, char** argv)
{
    int argCount = 1;
    std::stringstream ss;
    float fTemp = 0.0;
    std::string stringTempName;
    std::string stringTemp;

    if( argc < m_minArgumentNumber)
    {
        return false;
    }

    while(argCount<argc)
    {
        if(strcmp(argv[argCount], "-upper") == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            ss<<argv[argCount];
            ss>>fTemp;
            m_fFloatTypeInputs.insert(std::pair<std::string, float>(stringTempName, fTemp));
            ss.str(std::string());
            ss.clear();
            argCount++;
        }
        else if(strcmp(argv[argCount], "-lower") == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            ss<<argv[argCount];
            ss>>fTemp;
            m_fFloatTypeInputs.insert(std::pair<std::string, float>(stringTempName, fTemp));
            ss.str(std::string());
            ss.clear();
            argCount++;
        }
        else if(strcmp(argv[argCount], "-i") == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            stringTemp = argv[argCount];
            m_StringTypeInputs.insert(std::pair<std::string, std::string>(stringTempName, stringTemp));
            argCount++;
        }
        else if(strcmp(argv[argCount], "-o") == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            stringTemp = argv[argCount];
            m_StringTypeInputs.insert(std::pair<std::string, std::string>(stringTempName, stringTemp));
            argCount++;
        }
        else if(strcmp(argv[argCount], "-sigma") == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            ss<<argv[argCount];
            ss>>fTemp;
            m_fFloatTypeInputs.insert(std::pair<std::string, float>(stringTempName, fTemp));
            ss.str(std::string());
            ss.clear();
            argCount++;
        }
        else if(strcmp(argv[argCount], "-saveOriginalEdgeMap") == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            stringTemp = argv[argCount];
            m_StringTypeInputs.insert(std::pair<std::string, std::string>(stringTempName, stringTemp));
            argCount++;
        }
        else
        {
            std::cerr<<"Unknown command line argument!"<<std::endl;
            return false;
        }

    }

    return true;
}


float ArgumentParsing::LookupFloatType(std::string entry)
{
    return (m_fFloatTypeInputs[entry]);
}


std::string ArgumentParsing::LookupStringType(std::string entry)
{
    return (m_StringTypeInputs[entry]);
}