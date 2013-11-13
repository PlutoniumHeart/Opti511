#ifndef BINARYOPENING_H
#define BINARYOPENING_H


#include "BinaryDilation.h"
#include "BinaryErosion.h"


class BinaryOpening : public BaseImage
{
public:
    BinaryOpening(std::string fileName, int width);
    ~BinaryOpening();

    virtual void Filter();
    virtual void Filter(unsigned char** input);
    virtual void Filter(unsigned char** input, int col, int row);

    void SaveResult(std::string fileName);
    void SaveResult(std::string fileName, int col, int row);

    void SetForeGround(unsigned char fg);
protected:
    int m_iBWidth;
    BinaryDilation* m_pDilation;
    BinaryErosion* m_pErosion;
};


#endif //BINARYOPENING_H
