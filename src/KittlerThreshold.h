#ifndef KITTLERTHRESHOLD_H
#define KITTLERTHRESHOLD_H


#include "Histogram.h"
#include "BaseImage.h"


class KittlerThreshold : public BaseImage, public Histogram
{
public:
    KittlerThreshold(std::string fileName);
    ~KittlerThreshold();

    void Filter();
    void Filter(unsigned char** input);
    void Filter(unsigned char** input, int col, int row);

    void SaveResult(std::string filename);
    void SaveResult(std::string filename, int col, int row);

    void SetColumns(int col);
    void SetRows(int row);
private:
    long long m_lPointerOffsetForResult;
    unsigned char** m_ppResult;
};


#endif // !KITTLERTHRESHOLD_H
