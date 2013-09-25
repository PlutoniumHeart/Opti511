#include "LoGEdge.h"


LoGEdge::LoGEdge()
    : BaseImage()
    , m_ppLoG(NULL)
    , m_ppEdgeMap(NULL)
    , m_lPointerOffsetForLoG(0)
    , m_lPointerOffsetForEdge(0)
    , m_bSaveAsOriginal(false)
    , m_fUpperThreshold(0.0)
    , m_fLowerThreshold(0.0)
{
    float sigma = 1.4;

    m_iLoGSize = 6.0*sqrt(2.0)*sigma;
    
    m_ppLoG = (float**)BaseImage::CreateMatrix(m_iLoGSize, m_iLoGSize, 0, 0, sizeof(float), &m_lPointerOffsetForLoG);
    for(int i=-(m_iLoGSize-1)/2;i<(m_iLoGSize+1)/2;i++)
    {
        for(int j=-(m_iLoGSize-1)/2;j<(m_iLoGSize+1)/2;j++)
        {
            m_ppLoG[i][j] = (-1.0/(M_PI*pow(sigma, 4.0))) * (1-(i*i+j*j)/(2.0*sigma*sigma)) * exp(-(i*i+j*j)/(2.0*sigma*sigma));
        }
    }
#ifdef _DEBUG
    for(int i=-(m_iLoGSize-1)/2;i<(m_iLoGSize+1)/2;i++)
    {
        for(int j=-(m_iLoGSize-1)/2;j<(m_iLoGSize+1)/2;j++)
        {
            std::cout<<m_ppLoG[j][i]<<" ";
        }
        std::cout<<std::endl;
    }
#endif
}


LoGEdge::LoGEdge(std::string filename, float sigma)
    : BaseImage(filename, -( (int)(6.0*sqrt(2.0)*sigma)%2==0 ? (6.0*sqrt(2.0)*sigma)+1 : (6.0*sqrt(2.0)*sigma) - 1 )/2, -( (int)(6.0*sqrt(2.0)*sigma)%2==0 ? (6.0*sqrt(2.0)*sigma)+1 : (6.0*sqrt(2.0)*sigma) - 1)/2 )
    , m_ppLoG(NULL)
    , m_ppEdgeMap(NULL)
    , m_lPointerOffsetForLoG(0)
    , m_lPointerOffsetForEdge(0)
    , m_bSaveAsOriginal(false)
    , m_fUpperThreshold(0.0)
    , m_fLowerThreshold(0.0)
{
    m_iLoGSize = (int)(6.0*sqrt(2.0)*sigma)%2==0 ? (6.0*sqrt(2.0)*sigma)+1 : (6.0*sqrt(2.0)*sigma);
    /*m_iLoGSize = 6.0*sqrt(2.0)*sigma;
    BaseImage(filename, -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2);*/

    m_ppLoG = (float**)BaseImage::CreateMatrix(m_iLoGSize+(m_iLoGSize-1), m_iLoGSize+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(float), &m_lPointerOffsetForLoG);
    for(int i=-(m_iLoGSize-1)/2;i<(m_iLoGSize+1)/2;i++)
    {
        for(int j=-(m_iLoGSize-1)/2;j<(m_iLoGSize+1)/2;j++)
        {
            m_ppLoG[i][j] = (-1.0/(M_PI*pow(sigma, 4.0))) * (1-(i*i+j*j)/(2.0*sigma*sigma)) * exp(-(i*i+j*j)/(2.0*sigma*sigma));
        }
    }
#ifdef _DEBUG
    for(int i=-(m_iLoGSize-1)/2;i<(m_iLoGSize+1)/2;i++)
    {
        for(int j=-(m_iLoGSize-1)/2;j<(m_iLoGSize+1)/2;j++)
        {
            std::cout<<m_ppLoG[j][i]<<" ";
        }
        std::cout<<std::endl;
    }
#endif
}


LoGEdge::~LoGEdge()
{
    m_ppLoG += m_lPointerOffsetForLoG;
    if(m_ppLoG != NULL)
    {
        free(m_ppLoG);
    }

    m_ppEdgeMap += m_lPointerOffsetForEdge;
    if(m_ppEdgeMap != NULL)
    {
        free(m_ppEdgeMap);
    }
}


void LoGEdge::Filter()
{
    Filter(m_ppImageMatrix);
}


void LoGEdge::Filter(unsigned char** input)
{
    Filter(input, m_iColumns, m_iRows);
}


void LoGEdge::Filter(unsigned char** input, int col, int row)
{
    int i = 0, j = 0;
    float max = 0.0, min = 0.0;
    long long tempPointerOffset = 0;
    float** tempEdge= (float**)BaseImage::CreateMatrix(m_iColumns+(m_iLoGSize-1), m_iRows+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(float), &tempPointerOffset);
    float** ppEdgeMapFloat = (float**)BaseImage::CreateMatrix(m_iColumns+(m_iLoGSize-1), m_iRows+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(float), &tempPointerOffset);
    m_ppEdgeMap = (unsigned char**)BaseImage::CreateMatrix(m_iColumns+(m_iLoGSize-1), m_iRows+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(unsigned char), &m_lPointerOffsetForEdge);
    if(m_bSaveAsOriginal)
    {
        m_ppOriginalEdgeMap = (unsigned char**)CreateMatrix(m_iColumns+(m_iLoGSize-1), m_iRows+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(unsigned char), &m_lPointerOffsetForEdge);
    }

    if(m_fLowerThreshold > m_fUpperThreshold)
	{
		std::cerr<<"Lower threshold is bigger than the upper threshold!"<<std::endl;
		return;
	}

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            float temp = 0.0;
            for(int x=-(m_iLoGSize-1)/2;x<(m_iLoGSize+1)/2;x++)
            {
                for(int y=-(m_iLoGSize-1)/2;y<(m_iLoGSize+1)/2;y++)
                {
                    temp += input[i+x][j+y]*m_ppLoG[x][y];
                }
            }
            if(temp>max)
            {
                max = temp;
            }
            if(temp<min)
            {
                min = temp;
            }
            ppEdgeMapFloat[i][j] = temp;
        }
    }

    if(m_bSaveAsOriginal)
	{
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				m_ppOriginalEdgeMap[i][j] = (unsigned char)(255.0-(ppEdgeMapFloat[i][j]/(max-min)*255.0)); // Edge is black
			}
		}
	}

    for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if(ppEdgeMapFloat[i][j]>m_fUpperThreshold)
            {
                m_ppEdgeMap[i][j] = 0; // Edge is black
            }
			else if(ppEdgeMapFloat[i][j]<=m_fUpperThreshold && ppEdgeMapFloat[i][j]>m_fLowerThreshold)
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
	ppEdgeMapFloat += tempPointerOffset;
    if(ppEdgeMapFloat != NULL)
    {
        free(ppEdgeMapFloat);
    }
}


void LoGEdge::SaveAsOriginal(bool b)
{
	m_bSaveAsOriginal = b;
}


void LoGEdge::Resolveambiguity()
{
	std::vector<PixelLocation>::iterator itr;
	bool next = false;
	int statistics = 0;

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
}


void LoGEdge::SaveEdgeMap(std::string filename)
{
    SaveEdgeMap(filename, m_iColumns, m_iRows);
}


void LoGEdge::SaveEdgeMap(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppEdgeMap, 0, 0, col, row);
}


void LoGEdge::SaveOriginalEdgeMap(std::string filename)
{
    SaveOriginalEdgeMap(filename, m_iColumns, m_iRows);
}


void LoGEdge::SaveOriginalEdgeMap(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppOriginalEdgeMap, 0, 0, col, row);
}


void LoGEdge::SetUpperThreshold(float upThreshold)
{
    m_fUpperThreshold = upThreshold;
}


float LoGEdge::GetUpperThreshold()
{
    return m_fUpperThreshold;
}


void LoGEdge::SetLowerThreshold(float lowerThreshold)
{
	m_fLowerThreshold = lowerThreshold;
}


float LoGEdge::GetLowerThreshold()
{
	return m_fLowerThreshold;
}


void LoGEdge::SetColumns(int col)
{
	m_iColumns = col;
}


void LoGEdge::SetRows(int row)
{
	m_iRows = row;
}