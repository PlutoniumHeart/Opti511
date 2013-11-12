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

    m_fFloatTypeInputs.insert(std::pair<std::string, float>("-0", -1.0));
    m_fFloatTypeInputs.insert(std::pair<std::string, float>("-s", 0.0));

    while(argCount<argc)
    {
        if(strncmp(argv[argCount], "-upper", 6) == 0)
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
        else if(strncmp(argv[argCount], "-lower", 6) == 0)
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
        else if(strncmp(argv[argCount], "-i", 2) == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            stringTemp = argv[argCount];
            m_StringTypeInputs.insert(std::pair<std::string, std::string>(stringTempName, stringTemp));
            argCount++;
        }
        else if(strncmp(argv[argCount], "-o", 2) == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            stringTemp = argv[argCount];
            m_StringTypeInputs.insert(std::pair<std::string, std::string>(stringTempName, stringTemp));
            argCount++;
        }
        else if(strncmp(argv[argCount], "-sigma", 6) == 0)
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
        else if(strncmp(argv[argCount], "-saveOriginalEdgeMap", 20) == 0)
        {
            stringTempName = argv[argCount];
            argCount++;
            stringTemp = argv[argCount];
            m_StringTypeInputs.insert(std::pair<std::string, std::string>(stringTempName, stringTemp));
            argCount++;
        }
        else if(strncmp(argv[argCount], "-0", 2) == 0)
        {
            if(LookupFloatType("-1")!=0)
            {
                std::cerr<<"\"-1\" parameter cannot be used together with \"-0\""<<std::endl;
                return false;
            }
            stringTempName = argv[argCount];
            std::map<std::string, float>::iterator itr = m_fFloatTypeInputs.find("-0");
            if(itr!=m_fFloatTypeInputs.end())
            {
                itr->second = 0;
            }
            argCount++;
        }
        else if(strncmp(argv[argCount], "-1", 2) == 0)
        {
            float temp = LookupFloatType("-0");
            if(LookupFloatType("-0")==0)
            {
                std::cerr<<"\"-0\" parameter cannot be used together with \"-1\""<<std::endl;
                return false;
            }
            stringTempName = argv[argCount];
            m_fFloatTypeInputs.insert(std::pair<std::string, float>(stringTempName, 255.0));
            argCount++;
        }
        else if(strncmp(argv[argCount], "-s", 2) == 0)
        {
            stringTempName = argv[argCount];
            std::map<std::string, float>::iterator itr = m_fFloatTypeInputs.find("-s");
            if(itr!=m_fFloatTypeInputs.end())
            {
                itr->second = 1.0;
            }
            argCount++;
        }
	else if(strncmp(argv[argCount], "-w", 2) == 0)
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
