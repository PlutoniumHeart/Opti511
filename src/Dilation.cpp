#include "BinaryDilation.h"
#include "ArgumentParsing.h"


int main(int argc, char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(7);
    if(!parser->Parse(argc, argv))
    {
	std::cerr<<"Usage: "<<argv[0]<<" [-0, -1] -i infile.pgm -o outputfile.pgm -w diskWidth"<<std::endl;
	return -1;
    }

    BinaryDilation* dilate = new BinaryDilation(parser->LookupStringType("-i"), parser->LookupFloatType("-w"));

    if(parser->LookupFloatType("-0")==0)
	dilate->SetForeGround(parser->LookupFloatType("-0"));
    else
	dilate->SetForeGround(parser->LookupFloatType("-1"));
    
    dilate->Filter();
    
    dilate->SaveResult(parser->LookupStringType("-o"));

    delete parser;
    delete dilate;
    return 0;
}
