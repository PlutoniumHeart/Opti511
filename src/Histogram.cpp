#include "Histogram.h"


Histogram::Histogram()
    : m_usHisto(NULL)
    , m_dP(NULL)
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

    if(m_dP!=NULL)
    {
        delete [] m_dP;
        m_dP = NULL;
    }
}


void Histogram::CreateHisto(unsigned char** input, int col, int row, int size)
{
    int i = 0, j = 0;
    m_usHisto = new unsigned short[size];
    memset(m_usHisto, 0, size*sizeof(unsigned short));
    m_dP = new double[size];
    memset(m_dP, 0, size*sizeof(unsigned short));

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            m_usHisto[input[i][j]]++;
        }
    }

    for(i=0;i<=UCHAR_MAX;i++)
    {
        m_lTotal += m_usHisto[i];
    }

    for(i=0;i<=UCHAR_MAX;i++)
    {
        m_dP[i] = (double)m_usHisto[i]/m_lTotal;
    }
}


int Histogram::Mean(int start, int end)
{
    int i = 0;
    double sum = 0.0;

    for(i=start;i<=end;i++)
    {
        sum += i*m_dP[i];
    }
    return sum;
}


double Histogram::Q(int t)
{
    int i = 0;
    double tot = 0.0; 

    for(i=0;i<=t;i++)
    {
        tot += m_dP[i];
    }

    return tot;
}
