#ifndef NONMAXSUPPRESSION_H
#define NONMAXSUPPRESSION_H


#define _USE_MATH_DEFINES
#include <cmath>
#include "BaseImage.h"


class NonMaxSuppression
{
public:
    NonMaxSuppression();
    ~NonMaxSuppression();

    void SetInterpolate(bool interpolate);
    bool GetInterpolate();
protected:
    float** m_ppGradientDirection;
    bool m_bInterpolate;
    
    void Suppress(int col, int row, float** input, float** output);
    void AllocateMemory(int col, int row, int startCol, int startRow);
private:
    long long m_lPointerOffset;
};


#endif // !NONMAXSUPPRESSION_H
