#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include <cstdlib>
#include <iostream>


class Histogram
{
public:
    Histogram();
    ~Histogram();
private:
    unsigned short *m_usHisto;
};


#endif // !HISTOGRAM_H
