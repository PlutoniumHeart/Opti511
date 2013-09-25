#include "LoGEdge.h"


LoGEdge::LoGEdge(std::string filename, float sigma)
    : BaseImage(filename, -( (int)(6.0*sqrt(2.0)*sigma)%2==0 ? (6.0*sqrt(2.0)*sigma)+1 : (6.0*sqrt(2.0)*sigma) - 1 )/2, -( (int)(6.0*sqrt(2.0)*sigma)%2==0 ? (6.0*sqrt(2.0)*sigma)+1 : (6.0*sqrt(2.0)*sigma) - 1)/2 )
    , m_ppOperator(NULL)
    , m_ppResult(NULL)
    , m_lPointerOffsetForOperator(0)
    , m_lPointerOffsetForResult(0)
    , m_bSaveAsRaw(false)
    , m_fUpperThreshold(0.0)
    , m_fLowerThreshold(0.0)
{
    m_iLoGSize = (int)(6.0*sqrt(2.0)*sigma)%2==0 ? (6.0*sqrt(2.0)*sigma)+1 : (6.0*sqrt(2.0)*sigma);
    m_ppOperator = (float**)BaseImage::CreateMatrix(m_iLoGSize+(m_iLoGSize-1), m_iLoGSize+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(float), &m_lPointerOffsetForOperator);
    for(int i=-(m_iLoGSize-1)/2;i<(m_iLoGSize+1)/2;i++)
    {
        for(int j=-(m_iLoGSize-1)/2;j<(m_iLoGSize+1)/2;j++)
        {
            m_ppOperator[i][j] = (-1.0/(M_PI*pow(sigma, 4.0))) * (1-(i*i+j*j)/(2.0*sigma*sigma)) * exp(-(i*i+j*j)/(2.0*sigma*sigma));
        }
    }
#ifdef _DEBUG
    for(int i=-(m_iLoGSize-1)/2;i<(m_iLoGSize+1)/2;i++)
    {
        for(int j=-(m_iLoGSize-1)/2;j<(m_iLoGSize+1)/2;j++)
        {
            std::cout<<m_ppOperator[j][i]<<" ";
        }
        std::cout<<std::endl;
    }
#endif
}


LoGEdge::~LoGEdge()
{
    if(m_ppOperator != NULL)
    {
        m_ppOperator += m_lPointerOffsetForOperator;
        free(m_ppOperator);
        m_ppOperator = NULL;
    }

    if(m_ppResult != NULL)
    {
        m_ppResult += m_lPointerOffsetForResult;
        free(m_ppResult);
        m_ppResult = NULL;
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
    m_ppResult = (unsigned char**)BaseImage::CreateMatrix(m_iColumns+(m_iLoGSize-1), m_iRows+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(unsigned char), &m_lPointerOffsetForResult);
    if(m_bSaveAsRaw)
    {
        m_ppRawResult = (unsigned char**)CreateMatrix(m_iColumns+(m_iLoGSize-1), m_iRows+(m_iLoGSize-1), -(m_iLoGSize-1)/2, -(m_iLoGSize-1)/2, sizeof(unsigned char), &m_lPointerOffsetForResult);
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
                    temp += input[i+x][j+y]*m_ppOperator[x][y];
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

    if(m_bSaveAsRaw)
	{
		for(i=0;i<row;i++)
		{
			for(j=0;j<col;j++)
			{
				m_ppRawResult[i][j] = (unsigned char)(255.0-(ppEdgeMapFloat[i][j]/(max-min)*255.0)); // Edge is black
			}
		}
	}

    for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if(ppEdgeMapFloat[i][j]>m_fUpperThreshold)
            {
                m_ppResult[i][j] = 0; // Edge is black
            }
			else if(ppEdgeMapFloat[i][j]<=m_fUpperThreshold && ppEdgeMapFloat[i][j]>m_fLowerThreshold)
			{
				m_MaybePixels.push_back(PixelLocation(j, i)); // Remember maybe-pixels
			}
            else
            {
                m_ppResult[i][j] = 255;
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


void LoGEdge::SaveAsRaw(bool b)
{
	m_bSaveAsRaw = b;
}


void LoGEdge::Resolveambiguity()
{
	std::vector<PixelLocation>::iterator itr;
	bool next = false;
	int statistics = 0;

	for(itr=m_MaybePixels.begin();itr!=m_MaybePixels.end();itr++)
	{
		m_ppResult[itr->row][itr->col] = 255;
		for(int i=-1;i<2;i++)
		{
			for(int j=-1;j<2;j++)
			{
				if(m_ppResult[itr->row+i][itr->col+j] == 0)
				{
					m_ppResult[itr->row][itr->col] = 0; // Edge is black
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


void LoGEdge::SaveResult(std::string filename)
{
    SaveResult(filename, m_iColumns, m_iRows);
}


void LoGEdge::SaveResult(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppResult, 0, 0, col, row);
}


void LoGEdge::SaveRawResult(std::string filename)
{
    SaveRawResult(filename, m_iColumns, m_iRows);
}


void LoGEdge::SaveRawResult(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppRawResult, 0, 0, col, row);
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