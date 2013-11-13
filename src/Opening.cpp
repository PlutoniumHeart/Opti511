#include "BinaryOpening.h"
#include "ArgumentParsing.h"


int main(int argc,char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(7);
    if(!parser->Parse(argc, argv))
    {
        std::cerr<<"Usage: "<<argv[0]<<"[-0, -1] -i infile.pgm -o outfile.pgm -w diskWidth"<<std::endl;
        return -1;
    }

    BinaryOpening* open = new BinaryOpening(parser->LookupStringType("-i"), parser->LookupFloatType("-w"));

    /*if(parser->LookupFloatType("-0")==0)
        open->SetForeGround(parser->LookupFloatType("-0"));
    else
        open->SetForeGround(parser->LookupFloatType("-1"));
    */

    open->Filter();

    open->SaveResult(parser->LookupStringType("-o"));

    delete parser;
    delete open;
    return 0;
}
