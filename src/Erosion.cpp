#include "BinaryErosion.h"
#include "ArgumentParsing.h"


int main(int argc, char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(7);
    if(!parser->Parse(argc, argv))
    {
        std::cerr<<"Usage: "<<argv[0]<<" [-0, -1] -i infile.pgm -o outputfile.pgm -w diskWidth"<<std::endl;
        return -1;
    }

    BinaryErosion* erode = new BinaryErosion(parser->LookupStringType("-i"), parser->LookupFloatType("-w"));

    if(parser->LookupFloatType("-0")==0)
        erode->SetForeGround(parser->LookupFloatType("-0"));
    else
        erode->SetForeGround(parser->LookupFloatType("-1"));
    
    erode->Filter();
    
    erode->SaveResult(parser->LookupStringType("-o"));

    delete parser;
    delete erode;
    return 0;
}
