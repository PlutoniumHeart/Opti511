#include "SobelEdge.h"


int main(int argc, char** argv)
{
	if(argc<=5 && argc > 6)
	{
		std::cerr<<"Usage: "<<argv[0]<<" [-o/-i] upperThreshold lowerThreshold inputImage outputEdgemap"<<std::endl;
		return -1;
	}
	else if(argc == 6)
	{
		SobelEdge* SobelFilter = new SobelEdge(argv[4]);

		if(argv[1][0]=='-' && argv[1][1] == 'o')
		{
			SobelFilter->SaveAsOriginal(true);
		}
		else if(argv[1][0]=='-' && argv[1][1] == 'i')
		{
			SobelFilter->SetInterpolate(true);
		}

		std::stringstream ss(argv[2]);
		float upperThreshold;
		ss>>upperThreshold;
		ss.str(std::string());
		ss.clear();

		ss<<argv[3];
		float lowerThreshold;
		ss>>lowerThreshold;

		SobelFilter->SetUpperThreshold(upperThreshold);
		SobelFilter->SetLowerThreshold(lowerThreshold);
		SobelFilter->Filter();
		SobelFilter->SaveEdgeMap(argv[5]);

		delete SobelFilter;
	}
	else
	{
		SobelEdge* SobelFilter = new SobelEdge(argv[3]);

		std::stringstream ss(argv[1]);
		float upperThreshold;
		ss>>upperThreshold;
		ss.str(std::string());
		ss.clear();

		float lowerThreshold;
		ss<<argv[2];
		ss>>lowerThreshold;

		SobelFilter->SetUpperThreshold(upperThreshold);
		SobelFilter->SetLowerThreshold(lowerThreshold);
		SobelFilter->Filter();
		SobelFilter->SaveEdgeMap(argv[4]);

		delete SobelFilter;
	}
    return 0;
}

// Other way of using this edge detection filter
/*
BaseImage* ImageReader = new BaseImage("../data/cmanswirl.pgm", -1, -1);
SobelEdge* SobelFilter = new SobelEdge;

SobelFilter->SaveAsOriginal(true);
SobelFilter->SetColumns(ImageReader->GetColumns());
SobelFilter->SetRows(ImageReader->GetRows());
SobelFilter->Filter(ImageReader->GetImagePointer());
SobelFilter->SaveEdgeMap("../data/alternative.pgm");

delete ImageReader;
delete SobelFilter;*/