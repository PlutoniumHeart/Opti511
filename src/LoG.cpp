#include "ArgumentParsing.h"
#include "LoGEdge.h"


int main(int argc, char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(10);
    if(!parser->Parse(argc, argv))
    {
        std::cerr<<"Usage: "<<argv[0]<<" -upper upperThreshold -lower lowerThreshold -sigma Sigma -i inputFile -o outputFile [-saveOriginalEdgeMap outputFile]"<<std::endl;
		return -1;
    }

    LoGEdge* LoGFilter = new LoGEdge(parser->LookupStringType("-i"), parser->LookupFloatType("-sigma"));

    LoGFilter->SetUpperThreshold(parser->LookupFloatType("-upper"));
    LoGFilter->SetLowerThreshold(parser->LookupFloatType("-lower"));
    if(parser->LookupStringType("-saveOriginalEdgeMap") != "")
    {
        LoGFilter->SaveAsRaw(true);
    }
    LoGFilter->Filter();
    LoGFilter->SaveResult(parser->LookupStringType("-o"));
    if(parser->LookupStringType("-saveOriginalEdgeMap") != "")
    {
        LoGFilter->SaveRawResult(parser->LookupStringType("-saveOriginalEdgeMap"));
    }

    delete LoGFilter;
    delete parser;
    return 0;
}
