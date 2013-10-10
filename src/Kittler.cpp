#include "ArgumentParsing.h"
#include "KittlerThreshold.h"


int main(int argc, char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(5);
    if(!parser->Parse(argc, argv))
    {
        std::cerr<<"Usage: "<<argv[0]<<" [-t threshold] -i inputImage -o outputImage"<<std::endl;
        return -1;
    }

    delete parser;
    return 0;
}