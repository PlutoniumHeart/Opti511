#ifndef LOGEDGE_H
#define LOGEDGE_H


#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "BaseImage.h"


class LoGEdge : BaseImage
{
public:
    LoGEdge();
    LoGEdge(std::string filename, float sigma);
    virtual ~LoGEdge();

    virtual void Filter();
    virtual void Filter(unsigned char** input);
    virtual void Filter(unsigned char** input, int col, int row);

    virtual void SaveEdgeMap(std::string filename);
    virtual void SaveEdgeMap(std::string filename, int col, int row);
    virtual void SaveOriginalEdgeMap(std::string filename);
    virtual void SaveOriginalEdgeMap(std::string filename, int col, int row);

    virtual void SetUpperThreshold(float upThreshold);
    virtual float GetUpperThreshold();
	virtual void SetLowerThreshold(float lowThreshold);
	virtual float GetLowerThreshold();

    void SetColumns(int col);
	void SetRows(int row);

    void SaveAsOriginal(bool b);
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
    long long m_lPointerOffsetForLoG;
    long long m_lPointerOffsetForEdge;
    float** m_ppLoG;
    unsigned char** m_ppEdgeMap;
    unsigned char** m_ppOriginalEdgeMap;
    int m_iLoGSize;
    bool m_bSaveAsOriginal;
    float m_fUpperThreshold;
	float m_fLowerThreshold;
    std::vector<PixelLocation> m_MaybePixels;
};


#endif // !LOGEDGE_H
