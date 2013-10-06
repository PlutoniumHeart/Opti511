#include "ArgumentParsing.h"
#include "SobelEdge.h"
#include "Utils.h"


int main(int argc, char** argv)
{
    ArgumentParsing* parser = new ArgumentParsing(8);
	if(!parser->Parse(argc, argv))
	{
		std::cerr<<"Usage: "<<argv[0]<<" -upper upperThreshold -lower lowerThreshold -i inputFile -o outputFile [-saveOriginalEdgeMap outputFile]"<<std::endl;
		return -1;
	}

    SobelEdge* SobelFilter = new SobelEdge(parser->LookupStringType("-i"));

    SobelFilter->SetUpperThreshold(parser->LookupFloatType("-upper"));
    SobelFilter->SetLowerThreshold(parser->LookupFloatType("-lower"));
    std::cout<<"-upper"<<SobelFilter->GetUpperThreshold()<<"-lower"<<SobelFilter->GetLowerThreshold()<<std::endl;
    if(parser->LookupStringType("-saveOriginalEdgeMap") != "")
    {
        SobelFilter->SaveAsOriginal(true);
    }
    SobelFilter->Filter();
    SobelFilter->SaveEdgeMap(parser->LookupStringType("-o"));
    if(parser->LookupStringType("-saveOriginalEdgeMap") != "")
    {
        SobelFilter->SaveOriginalEdgeMap(parser->LookupStringType("-saveOriginalEdgeMap"));
    }

	delete SobelFilter;
    delete parser;
    return 0;
}
