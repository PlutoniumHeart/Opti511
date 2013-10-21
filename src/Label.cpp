#include "ArgumentParsing.h"
#include "ConnectedComponentsLabelling.h"


int main(int argc, char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(5);
    if(!parser->Parse(argc, argv))
    {
        std::cerr<<"Usage: "<<argv[0]<<" [-0,-1] [-s] -i infile.pgm -o outputfile.pgm"<<std::endl;
        return -1;
    }

    ConnectedComponentsLabelling* LabellingFilter = new ConnectedComponentsLabelling(parser->LookupStringType("-i"));

    LabellingFilter->Filter();

//    if(parser->LookupStringType("-o")!="")
//    {
//        LabellingFilter->SaveResult(parser->LookupStringType("-o"));
//    }

    delete LabellingFilter;
    delete parser;
    return 0;
}
