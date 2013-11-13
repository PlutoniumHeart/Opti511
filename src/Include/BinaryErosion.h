#ifndef BINARYEROSION_H
#define BINARYEROSION_H



#include "BinaryDilation.h"


class BinaryErosion : public BinaryDilation
{
public:
    BinaryErosion(std::string fileName, int width);
    BinaryErosion(int col, int row, int width);
    ~BinaryErosion();

    virtual void Filter();
    virtual void Filter(unsigned char** input);
    virtual void Filter(unsigned char** input, int col, int row);
};



#endif //BINARYEROSION_H
