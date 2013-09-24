#include "SobelEdge.h"


SobelEdge::SobelEdge()
	: BaseImage()
    , m_ppEdgeMap(NULL)
    , m_lPointerOffset(0)
    , m_fThreshold(0.0)
	, m_bSaveAsOriginal(false)
    , m_statistic(0)
{
	m_SobelOperator1[0][0] = 1;
    m_SobelOperator1[0][1] = 2;
    m_SobelOperator1[0][2] = 1;
    
    m_SobelOperator1[1][0] = 0;
    m_SobelOperator1[1][1] = 0;
    m_SobelOperator1[1][2] = 0;

    m_SobelOperator1[2][0] = -1;
    m_SobelOperator1[2][1] = -2;
    m_SobelOperator1[2][2] = -1;


    m_SobelOperator2[0][0] = -1;
    m_SobelOperator2[0][1] = 0;
    m_SobelOperator2[0][2] = 1;
    
    m_SobelOperator2[1][0] = -2;
    m_SobelOperator2[1][1] = 0;
    m_SobelOperator2[1][2] = 2;

    m_SobelOperator2[2][0] = -1;
    m_SobelOperator2[2][1] = 0;
    m_SobelOperator2[2][2] = 1;
}


SobelEdge::SobelEdge(std::string filename)
    : BaseImage(filename, -1, -1)
    , m_ppEdgeMap(NULL)
    , m_lPointerOffset(0)
    , m_fThreshold(0.0)
    , m_bSaveAsOriginal(false)
    , m_statistic(0)
{
    m_SobelOperator1[0][0] = 1;
    m_SobelOperator1[0][1] = 2;
    m_SobelOperator1[0][2] = 1;
    
    m_SobelOperator1[1][0] = 0;
    m_SobelOperator1[1][1] = 0;
    m_SobelOperator1[1][2] = 0;

    m_SobelOperator1[2][0] = -1;
    m_SobelOperator1[2][1] = -2;
    m_SobelOperator1[2][2] = -1;


    m_SobelOperator2[0][0] = 1;
    m_SobelOperator2[0][1] = 0;
    m_SobelOperator2[0][2] = -1;
    
    m_SobelOperator2[1][0] = 2;
    m_SobelOperator2[1][1] = 0;
    m_SobelOperator2[1][2] = -2;

    m_SobelOperator2[2][0] = 1;
    m_SobelOperator2[2][1] = 0;
    m_SobelOperator2[2][2] = -1;
}


SobelEdge::~SobelEdge()
{
    m_ppEdgeMap += m_lPointerOffset;
    if(m_ppEdgeMap != NULL)
    {
        free(m_ppEdgeMap);
    }
}


void SobelEdge::Filter()
{
    Filter(m_ppImageMatrix);
}


void SobelEdge::Filter(unsigned char** input)
{
    Filter(input, m_iColumns, m_iRows);
}


void SobelEdge::Filter(unsigned char** input, int col, int row)
{
    int i = 0, j = 0;
    float tempAngle = 0;
    m_ppEdgeMap = (unsigned char**)CreateMatrix(col+2, row+2, -1, -1, sizeof(unsigned char), &m_lPointerOffset);
    AllocateMemory(col, row, 0, 0);
    float **tempEdge = NULL;

    long long tempPointerOffset;
    tempEdge = (float**)CreateMatrix(col+2, row+2, -1, -1, sizeof(float), &tempPointerOffset);

	float max = 0.0, min = 50000000;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            // Simple Sobel filter kernels.
            float temp = 0.0, temp1 = 0.0, temp2 = 0.0;
            temp = (float)(input[i-1][j-1]*m_SobelOperator1[0][0] + input[i-1][j]*m_SobelOperator1[0][1] + input[i-1][j+1]*m_SobelOperator1[0][2] + 
                        input[i][j-1]*m_SobelOperator1[1][0]   + input[i][j]*m_SobelOperator1[1][1]   + input[i][j+1]*m_SobelOperator1[1][2] + 
                        input[i+1][j-1]*m_SobelOperator1[2][0] + input[i+1][j]*m_SobelOperator1[2][1] + input[i+1][j+1]*m_SobelOperator1[2][2]);

            temp1 = (float)(input[i-1][j-1]*m_SobelOperator2[0][0] + input[i-1][j]*m_SobelOperator2[0][1] + input[i-1][j+1]*m_SobelOperator2[0][2] +
                        input[i][j-1]*m_SobelOperator2[1][0]   + input[i][j]*m_SobelOperator2[1][1]   + input[i][j+1]*m_SobelOperator2[1][2] +
                        input[i+1][j-1]*m_SobelOperator2[2][0] + input[i+1][j]*m_SobelOperator2[2][1] + input[i+1][j+1]*m_SobelOperator2[2][2]);

            temp2 = temp*temp + temp1*temp1;

            // Preparation for converting float type to unsigned char for saving unthresholded edgemap.
			if(temp2>max)
			{
				max = temp2;
			}
			if(temp2<min)
			{
				min = temp2;
			}
			tempEdge[i][j] = temp2;

            tempAngle = atan2(temp, temp1);

            m_ppGradientDirection[i][j] = tempAngle;
        }
    }
    // Converting float to unsigned char for saving.
    Suppress(m_iColumns, m_iRows, tempEdge);
	if(m_bSaveAsOriginal)
	{
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				m_ppEdgeMap[i][j] = (unsigned char)(255.0-(tempEdge[i][j]/(max-min)*255.0)); // Edge is black
			}
		}
	}
    else
    {
        for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				if(tempEdge[i][j]>m_fThreshold)
                {
                    m_ppEdgeMap[i][j] = 0; // Edge is black
                    m_statistic++;
                }
                else
                {
                    m_ppEdgeMap[i][j] = 255;
                }
			}
		}
    }
    tempEdge += tempPointerOffset;
    if(tempEdge != NULL)
    {
        free(tempEdge);
    }
    std::cout<<"Edge Pixels: "<<m_statistic<<std::endl;
}


void SobelEdge::SaveEdgeMap(std::string filename)
{
    SaveEdgeMap(filename, m_iColumns, m_iRows);
}


void SobelEdge::SaveEdgeMap(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppEdgeMap, 0, 0, col, row);
}


unsigned char** SobelEdge::GetEdgeMap()
{
	return m_ppEdgeMap;
}


void SobelEdge::SetThreshold(float threshold)
{
    m_fThreshold = threshold;
}


float SobelEdge::GetThreshold()
{
    return m_fThreshold;
}


void SobelEdge::SaveAsOriginal(bool b)
{
	m_bSaveAsOriginal = b;
}


void SobelEdge::SetColumns(int col)
{
	m_iColumns = col;
}


void SobelEdge::SetRows(int row)
{
	m_iRows = row;
}