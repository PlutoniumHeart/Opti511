#include "NonMaxSuppression.h"


NonMaxSuppression::NonMaxSuppression()
    : m_bInterpolate(false)
    , m_ppGradientDirection(NULL)
{
}


NonMaxSuppression::~NonMaxSuppression()
{
    m_ppGradientDirection += m_lPointerOffset;
    if(m_ppGradientDirection != NULL)
    {
        free(m_ppGradientDirection);
    }
}


void NonMaxSuppression::SetInterpolate(bool interpolate)
{
    m_bInterpolate = interpolate;
}


bool NonMaxSuppression::GetInterpolate()
{
    return m_bInterpolate;
}


void NonMaxSuppression::Suppress(int col, int row, float** input)
{
    int i = 0, j = 0;

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(!m_bInterpolate)
            {
                if( (m_ppGradientDirection[i][j]<=M_PI/8.0 && m_ppGradientDirection[i][j]>-M_PI/8.0) || 
                    (m_ppGradientDirection[i][j]>7.0*M_PI/8.0) || 
                    (m_ppGradientDirection[i][j]<=-7.0*M_PI/8.0) )
                {
                    if( input[i][j]>=input[i][j+1] && input[i][j]>=input[i][j-1] )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
                else if( (m_ppGradientDirection[i][j]>M_PI/8.0 && m_ppGradientDirection[i][j]<=M_PI/4.0) || 
                         (m_ppGradientDirection[i][j]<-5.0*M_PI/8.0) || 
                         (m_ppGradientDirection[i][j]>=-7.0*M_PI/8.0) )
                {
                    if( input[i][j]>=input[i-1][j+1] && input[i][j]>=input[i+1][j-1] )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
                else if( (m_ppGradientDirection[i][j]>M_PI/4.0 && m_ppGradientDirection[i][j]<=5.0*M_PI/8.0) || 
                         (m_ppGradientDirection[i][j]<-M_PI/4.0) || 
                         (m_ppGradientDirection[i][j]>=-5.0*M_PI/8.0) )
                {
                    if( input[i][j]>=input[i-1][j] && input[i][j]>=input[i+1][j] )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
                else
                {
                    if( input[i][j]>=input[i-1][j-1] && input[i][j]>=input[i+1][j+1] )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
            }
            else
            {
                if( (m_ppGradientDirection[i][j]<M_PI/4.0 && m_ppGradientDirection[i][j]>=0.0) ||
					(m_ppGradientDirection[i][j]>=-M_PI && m_ppGradientDirection[i][j]<-3.0*M_PI/4.0) )
                {
                    float temp1 = input[i-1][j+1]*tan(m_ppGradientDirection[i][j]) + (1.0-tan(m_ppGradientDirection[i][j]))*input[i][j+1];
                    float temp2 = input[i+1][j-1]*tan(m_ppGradientDirection[i][j]) + (1.0-tan(m_ppGradientDirection[i][j]))*input[i][j-1];

                    if( input[i][j]>=temp1 && input[i][j]>=temp2 )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
                else if( (m_ppGradientDirection[i][j]<M_PI/2.0 && m_ppGradientDirection[i][j]>=M_PI/4.0) ||
						 (m_ppGradientDirection[i][j]>=-3.0*M_PI/4.0 && m_ppGradientDirection[i][j]<-M_PI/2.0) )
                {
                    float temp1 = input[i-1][j+1]*(1.0/tan(m_ppGradientDirection[i][j])) + (1.0-1.0/tan(m_ppGradientDirection[i][j])*input[i-1][j]);
                    float temp2 = input[i+1][j-1]*(1.0/tan(m_ppGradientDirection[i][j])) + (1.0-1.0/tan(m_ppGradientDirection[i][j])*input[i+1][j]);

                    if( input[i][j]>=temp1 && input[i][j]>=temp2 )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
                else if( (m_ppGradientDirection[i][j]<3.0*M_PI/4.0 && m_ppGradientDirection[i][j]>=M_PI/2.0) ||
						 (m_ppGradientDirection[i][j]>=-M_PI/2.0 && m_ppGradientDirection[i][j]<-M_PI/4.0) )
                {
                    float temp1 = input[i-1][j-1]*(1.0/(-tan(m_ppGradientDirection[i][j]))) + (1.0-1.0/(-tan(m_ppGradientDirection[i][j])))*input[i-1][j];
                    float temp2 = input[i+1][j+1]*(1.0/(-tan(m_ppGradientDirection[i][j]))) + (1.0-1.0/(-tan(m_ppGradientDirection[i][j])))*input[i+1][j];

                    if( input[i][j]>=temp1 && input[i][j]>=temp2 )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
                else if( (m_ppGradientDirection[i][j]<=3.141593 && m_ppGradientDirection[i][j]>=3.0*M_PI/4.0) ||
						  (m_ppGradientDirection[i][j]>=-M_PI/4.0 && m_ppGradientDirection[i][j]<0.0) )
                {
                    float temp1 = input[i-1][j-1]*(-tan(m_ppGradientDirection[i][j])) + input[i][j-1]*(1.0-(-tan(m_ppGradientDirection[i][j])));
                    float temp2 = input[i+1][j+1]*(-tan(m_ppGradientDirection[i][j])) + input[i][j+1]*(1.0-(-tan(m_ppGradientDirection[i][j])));

                    if( input[i][j]>=temp1 && input[i][j]>=temp2 )
                    {
                        input[i][j] = input[i][j];
                    }
                    else
                    {
                        input[i][j] = 0.0;
                    }
                }
            }
        }
    }
}


void NonMaxSuppression::AllocateMemory(int col, int row, int startCol, int startRow)
{
    m_ppGradientDirection = (float**)BaseImage::CreateMatrix(col, row, 0, 0, sizeof(float), &m_lPointerOffset);
}