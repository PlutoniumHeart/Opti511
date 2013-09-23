#include "SobelEdge.h"


int main(int argc, char** argv)
{
	if(argc<=4 && argc > 5)
	{
		std::cerr<<"Usage: "<<argv[0]<<" [-o] threshold inputImage outputEdgemap"<<std::endl;
		return -1;
	}
	else if(argc == 5)
	{
		SobelEdge* SobelFilter = new SobelEdge(argv[3]);

		if(argv[1][0]=='-' && argv[1][1] == 'o')
		{
			SobelFilter->SaveAsOriginal(true);
		}

		std::stringstream ss(argv[2]);
		float threshold;
		ss>>threshold;

		SobelFilter->SetThreshold(threshold);
		SobelFilter->Filter();
		SobelFilter->SaveEdgeMap(argv[4]);

		delete SobelFilter;
	}
	else
	{
		SobelEdge* SobelFilter = new SobelEdge(argv[2]);

		std::stringstream ss(argv[1]);
		float threshold;
		ss>>threshold;

        SobelFilter->SetInterpolate(true);
		SobelFilter->SetThreshold(threshold);
		SobelFilter->Filter();
		SobelFilter->SaveEdgeMap(argv[3]);

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