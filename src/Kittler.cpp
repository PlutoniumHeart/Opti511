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

    KittlerThreshold* threshold = new KittlerThreshold(parser->LookupStringType("-i"));

    if(parser->LookupFloatType("-t")!=0)
    {
        threshold->SetUserThreshold(parser->LookupFloatType("-t"));
    }
    threshold->Filter();
    threshold->SaveResult(parser->LookupStringType("-o"));

    delete parser;
    delete threshold;
    return 0;
}
