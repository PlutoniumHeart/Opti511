#include "BinaryDilation.h"
#include "ArgumentParsing.h"


int main(int argc, char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(7);
    if(!parser->Parse(argc, argv))
    {
	std::cerr<<"Usage: "<<argv[0]<<"-i infile.pgm -o outputfile.pgm -w diskWidth"<<std::endl;
	return -1;
    }

    std::cout<<"1"<<std::endl;
    BinaryDilation* dilate = new BinaryDilation(parser->LookupStringType("-i"), parser->LookupFloatType("-w"));

    std::cout<<"2"<<std::endl;
    dilate->Filter();

    dilate->SaveResult(parser->LookupStringType("-o"));

    delete parser;
    delete dilate;
    return 0;
}
