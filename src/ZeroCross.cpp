#include "ZeroCross.h"


ZeroCross::ZeroCross()
	: m_ppSecondDerivative(NULL)
{
}


ZeroCross::~ZeroCross()
{
	if(m_ppSecondDerivative!=NULL)
	{
		m_ppSecondDerivative += m_lPointerOffset;
		free(m_ppSecondDerivative);
		m_ppSecondDerivative = NULL;
	}
}


void ZeroCross::AllocateMemoryForZC(int col, int row, int startCol, int startRow)
{
	m_ppSecondDerivative = (float**)BaseImage::CreateMatrix(col, row, startCol, startRow, sizeof(float), &m_lPointerOffset);
}


void ZeroCross::FindZeroCross(int col, int row, unsigned char** output)
{
    int i = 0, j = 0;

    BaseImage::Reflect<float>(col, row, 1, m_ppSecondDerivative);

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            std::vector<PixelLocation> Neighbors;
            output[i][j] = 255;
            if( GetSign(m_ppSecondDerivative[i-1][j-1]) != GetSign(m_ppSecondDerivative[i+1][j+1]) )
            {
                if( GetSign(m_ppSecondDerivative[i][j]) == GetSign(m_ppSecondDerivative[i-1][j-1]) )
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i+1][j+1]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
                else
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i-1][j-1]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
            }
            if( GetSign(m_ppSecondDerivative[i][j-1]) != GetSign(m_ppSecondDerivative[i][j+1]) )
            {
                if( GetSign(m_ppSecondDerivative[i][j]) == GetSign(m_ppSecondDerivative[i][j-1]) )
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i][j+1]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
                else
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i][j+1]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
            }
            if( GetSign(m_ppSecondDerivative[i-1][j+1]) != GetSign(m_ppSecondDerivative[i+1][j-1]) )
            {
                if( GetSign(m_ppSecondDerivative[i][j]) == GetSign(m_ppSecondDerivative[i-1][j+1]) )
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i+1][j-1]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
                else
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i-1][j+1]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
            }
            if( GetSign(m_ppSecondDerivative[i-1][j]) != GetSign(m_ppSecondDerivative[i+1][j]) )
            {
                if( GetSign(m_ppSecondDerivative[i][j]) == GetSign(m_ppSecondDerivative[i-1][j]) )
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i+1][j]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
                else
                {
                    if( std::abs(m_ppSecondDerivative[i][j]) <= std::abs(m_ppSecondDerivative[i-1][j]) )
                    {
                        output[i][j] = 0; // Black edge
                    }
                }
            }
        }
    }
}


int ZeroCross::GetSign(float input)
{
    if(input>=0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}