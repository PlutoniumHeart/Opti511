#include "Histogram.h"


Histogram::Histogram()
    : m_usHisto(NULL)
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