#include "SobelEdge.h"


int main(int argc, char** argv)
{
	if(argc<=8)
	{
		std::cerr<<"Usage: "<<argv[0]<<" -upper upperThreshold -lower lowerThreshold -i inputFile -o outputFile [-saveOriginalEdgeMap outputFile]"<<std::endl;
		return -1;
	}

    int argCount = 1;
    std::stringstream ss;
    std::string inputFile;
    std::string outputFile;
    bool saveOriginalEdgeMap = false;
    std::string originalEdgeMapOutput;
    float UpperThreshold = 0.0, LowerThreshold = 0.0;
    bool inputFileSet = false;
    bool outputFileSet = false;
    bool upperThresholdSet = false;
    bool lowerThresholdSet = false;
    bool saveOriginal = false;

    while(argCount<argc)
    {
        if(strcmp(argv[argCount], "-upper") == 0)
        {
            argCount++;
            ss<<argv[argCount];
            ss>>UpperThreshold;
            ss.str(std::string());
            ss.clear();
            upperThresholdSet = true;
            argCount++;
        }
        else if(strcmp(argv[argCount], "-lower") == 0)
        {
            argCount++;
            ss<<argv[argCount];
            ss>>LowerThreshold;
            ss.str(std::string());
            ss.clear();
            lowerThresholdSet = true;
            argCount++;
        }
        else if(strcmp(argv[argCount], "-i") == 0)
        {
            argCount++;
            inputFile = argv[argCount];
            inputFileSet = true;
            argCount++;
        }
        else if(strcmp(argv[argCount], "-o") == 0)
        {
            argCount++;
            outputFile = argv[argCount];
            outputFileSet = true;
            argCount++;
        }
        else if(strcmp(argv[argCount], "-saveOriginalEdgeMap") == 0)
        {
            argCount++;
            originalEdgeMapOutput = argv[argCount];
            saveOriginal = true;
            argCount++;
        }
        else
        {
            std::cerr<<"Unknown command line argument!"<<std::endl;
            return -1;
        }
    }

    if(!(upperThresholdSet && lowerThresholdSet &&  inputFileSet &&outputFileSet))
    {
        std::cerr<<"Usage: "<<argv[0]<<" -upper upperThreshold -lower lowerThreshold -i inputFile -o outputFile [-saveOriginalEdgeMap outputFile]"<<std::endl;
        return -1;
    }

    SobelEdge* SobelFilter = new SobelEdge(inputFile);

    SobelFilter->SetUpperThreshold(UpperThreshold);
    SobelFilter->SetLowerThreshold(LowerThreshold);
    if(saveOriginal)
    {
        SobelFilter->SaveAsOriginal(true);
    }
    SobelFilter->Filter();
    SobelFilter->SaveEdgeMap(outputFile);
    if(saveOriginal)
    {
        SobelFilter->SaveOriginalEdgeMap(originalEdgeMapOutput);
    }

	delete SobelFilter;
    return 0;
}