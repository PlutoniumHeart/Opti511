#include "Histogram.h"


Histogram::Histogram()
    : m_usHisto(NULL)
    , m_lTotal(0)
{
}


Histogram::~Histogram()
{
    if(m_usHisto!=NULL)
    {
        delete [] m_usHisto;
        m_usHisto = NULL;
    }
}


void Histogram::CreateHisto(unsigned char** input, int col, int row, int size)
{
    int i = 0, j = 0;
    m_usHisto = new unsigned short[size];
    memset(m_usHisto, 0, size*sizeof(unsigned short));

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            m_usHisto[input[i][j]]++;
        }
    }

    for(i=0;i<255;i++)
    {
        m_lTotal += m_usHisto[i];
    }
}


int Histogram::Mean(int start, int end)
{
    int i = 0;
    double sum = 0.0;
    double tot = 0.0;

    for(i=start;i<=end;i++)
    {
        tot += m_usHisto[i];
        sum += i*m_usHisto[i];
    }
    return (int)floor(sum/tot);
}


double Histogram::Q(int t)
{
    int i = 0;
    double tot = 0.0; 

    for(i=0;i<=t;i++)
    {
        tot += m_usHisto[i];
    }

    return tot/m_lTotal;
}
