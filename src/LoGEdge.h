#ifndef LOGEDGE_H
#define LOGEDGE_H


#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "BaseImage.h"


class LoGEdge : BaseImage
{
public:
    LoGEdge(std::string filename, float sigma);
    virtual ~LoGEdge();

    virtual void Filter();
    virtual void Filter(unsigned char** input);
    virtual void Filter(unsigned char** input, int col, int row);

    void SaveResult(std::string filename);
    void SaveResult(std::string filename, int col, int row);
    void SaveRawResult(std::string filename);
    void SaveRawResult(std::string filename, int col, int row);

    void SetUpperThreshold(float upThreshold);
    float GetUpperThreshold();
	void SetLowerThreshold(float lowThreshold);
	float GetLowerThreshold();

    void SetColumns(int col);
	void SetRows(int row);
    void SaveAsRaw(bool b);
protected:
    void Resolveambiguity();
private:
    struct PixelLocation
	{
		int col;
		int row;
		PixelLocation(int c, int r)
		{
			col = c;
			row = r;
		}
	};
private:
    long long m_lPointerOffsetForOperator;
    long long m_lPointerOffsetForResult;
    float** m_ppOperator;
    unsigned char** m_ppResult;
    unsigned char** m_ppRawResult;
    int m_iLoGSize;
    bool m_bSaveAsRaw;
    float m_fUpperThreshold;
	float m_fLowerThreshold;
    std::vector<PixelLocation> m_MaybePixels;
};


#endif // !LOGEDGE_H
