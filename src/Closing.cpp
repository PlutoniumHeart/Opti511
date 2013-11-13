#include "BinaryClosing.h"
#include "ArgumentParsing.h"


int main(int argc,char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(7);
    if(!parser->Parse(argc, argv))
    {
        std::cerr<<"Usage: "<<argv[0]<<"[-0, -1] -i infile.pgm -o outfile.pgm -w diskWidth"<<std::endl;
        return -1;
    }

    BinaryClosing* close = new BinaryClosing(parser->LookupStringType("-i"), parser->LookupFloatType("-w"));

    if(parser->LookupFloatType("-0")==0)
        close->SetForeGround(parser->LookupFloatType("-0"));
    else
        close->SetForeGround(parser->LookupFloatType("-1"));

    close->Filter();

    close->SaveResult(parser->LookupStringType("-o"));

    delete parser;
    delete close;
    return 0;
}
