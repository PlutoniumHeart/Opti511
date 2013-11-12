#ifndef BINARYDILATION_H
#define BINARYDILATION_H



#include "BaseImage.h"


class BinaryDilation : public BaseImage
{
public:
    BinaryDilation(std::string fileName, int width);
    ~BinaryDilation();

    void Filter();
    void Filter(unsigned char** input);
    void Filter(unsigned char** input, int col, int row);

    void SaveResult(std::string fileName);
    void SaveResult(std::string fileName, int col, int row);

    void SetForeGround(unsigned char fg);
private:
    int m_iBWidth;
    unsigned char** m_ppResult;
    long long m_lPointerOffsetForResult;
    unsigned char m_fg;
};



#endif //BINARYDILATION_H
