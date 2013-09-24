#include "SobelEdge.h"


SobelEdge::SobelEdge()
	: BaseImage()
    , m_ppEdgeMap(NULL)
    , m_ppOriginalEdgeMap(NULL)
    , m_lPointerOffset(0)
    , m_fUpperThreshold(0.0)
	, m_fLowerThreshold(0.0)
	, m_bSaveAsOriginal(false)
#ifdef _DEBUG
    , m_statistic(0)
#endif
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
    , m_ppOriginalEdgeMap(NULL)
    , m_lPointerOffset(0)
    , m_fUpperThreshold(0.0)
	, m_fLowerThreshold(0.0)
    , m_bSaveAsOriginal(false)
#ifdef _DEBUG
    , m_statistic(0)
#endif
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

    m_ppOriginalEdgeMap += m_lPointerOffset;
    if(m_ppOriginalEdgeMap != NULL)
    {
        free(m_ppOriginalEdgeMap);
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
    if(m_bSaveAsOriginal)
    {
        m_ppOriginalEdgeMap = (unsigned char**)CreateMatrix(col+2, row+2, -1, -1, sizeof(unsigned char), &m_lPointerOffset);
    }
    AllocateMemory(col, row, 0, 0);
    float **tempEdge = NULL;
	float **tempEdge1 = NULL;

    long long tempPointerOffset;
    tempEdge = (float**)CreateMatrix(col+2, row+2, -1, -1, sizeof(float), &tempPointerOffset);
	tempEdge1 = (float**)CreateMatrix(col+2, row+2, -1, -1, sizeof(float), &tempPointerOffset);

	float max = 0.0, min = 50000000;

	if(m_fLowerThreshold > m_fUpperThreshold)
	{
		std::cerr<<"Lower threshold is bigger than the upper threshold!"<<std::endl;
		return;
	}

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
    Suppress(m_iColumns, m_iRows, tempEdge, tempEdge1);
	if(m_bSaveAsOriginal)
	{
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				m_ppOriginalEdgeMap[i][j] = (unsigned char)(255.0-(tempEdge1[i][j]/(max-min)*255.0)); // Edge is black
			}
		}
	}
    for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if(tempEdge1[i][j]>m_fUpperThreshold)
            {
                m_ppEdgeMap[i][j] = 0; // Edge is black
#ifdef _DEBUG					
                m_statistic++;
#endif
            }
			else if(tempEdge1[i][j]<=m_fUpperThreshold && tempEdge1[i][j]>m_fLowerThreshold)
			{
				m_MaybePixels.push_back(PixelLocation(j, i)); // Remember maybe-pixels
			}
            else
            {
                m_ppEdgeMap[i][j] = 255;
            }
		}
	}
	Resolveambiguity(); // Resolve maybe-pixels

    tempEdge += tempPointerOffset;
    if(tempEdge != NULL)
    {
        free(tempEdge);
    }
	tempEdge1 += tempPointerOffset;
    if(tempEdge1 != NULL)
    {
        free(tempEdge1);
    }
#ifdef _DEBUG
    std::cout<<"Edge Pixels: "<<m_statistic<<std::endl;
#endif
}


void SobelEdge::SaveEdgeMap(std::string filename)
{
    SaveEdgeMap(filename, m_iColumns, m_iRows);
}


void SobelEdge::SaveEdgeMap(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppEdgeMap, 0, 0, col, row);
}


void SobelEdge::SaveOriginalEdgeMap(std::string filename)
{
    SaveOriginalEdgeMap(filename, m_iColumns, m_iRows);
}


void SobelEdge::SaveOriginalEdgeMap(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppOriginalEdgeMap, 0, 0, col, row);
}


unsigned char** SobelEdge::GetEdgeMap()
{
	return m_ppEdgeMap;
}


void SobelEdge::SetUpperThreshold(float upThreshold)
{
    m_fUpperThreshold = upThreshold;
}


float SobelEdge::GetUpperThreshold()
{
    return m_fUpperThreshold;
}


void SobelEdge::SetLowerThreshold(float lowerThreshold)
{
	m_fLowerThreshold = lowerThreshold;
}


float SobelEdge::GetLowerThreshold()
{
	return m_fLowerThreshold;
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


void SobelEdge::Resolveambiguity()
{
	std::vector<PixelLocation>::iterator itr;
	bool next = false;
	int statistics = 0;

#ifdef _DEBUG
	std::cout<<"Maybe pixel number: "<<m_MaybePixels.size()<<std::endl;
#endif

	for(itr=m_MaybePixels.begin();itr!=m_MaybePixels.end();itr++)
	{
		m_ppEdgeMap[itr->row][itr->col] = 255;
		for(int i=-1;i<2;i++)
		{
			for(int j=-1;j<2;j++)
			{
				if(m_ppEdgeMap[itr->row+i][itr->col+j] == 0)
				{
					m_ppEdgeMap[itr->row][itr->col] = 0; // Edge is black
					next = true;
#ifdef _DEBUG
					statistics++;
					m_statistic++;
#endif
					break;
				}
			}
			if(next)
			{
				next = !next;
				break;
			}
		}
	}
#ifdef _DEBUG
	std::cout<<statistics<<" confirmed as edges."<<std::endl;
#endif
}