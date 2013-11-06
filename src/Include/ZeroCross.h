#ifndef ZEROCROSS_H
#define ZEROCROSS_H


#include <vector>
#include "BaseImage.h"


class ZeroCross
{
public:
	ZeroCross();
	~ZeroCross();

protected:
	float** m_ppSecondDerivative;

	void AllocateMemoryForZC(int col, int row, int startCol, int startRow);
	void FindZeroCross(int col, int row, unsigned char** output);
private:
	long long m_lPointerOffset;
    int GetSign(float input);
};


#endif // !ZEROCROSS_H
