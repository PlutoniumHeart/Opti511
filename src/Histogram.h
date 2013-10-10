#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include <cstdlib>
#include <iostream>


class Histogram
{
public:
    Histogram();
    ~Histogram();
protected:
    void CreateHisto(unsigned char** input, int col, int row, int size);
    int Mean(int start, int end);
    double Q(int t);
protected:
    unsigned short *m_usHisto;
private:
    long m_lTotal;
};


#endif // !HISTOGRAM_H
