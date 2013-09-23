/* New image operation functions can be derived from existing classes, 
 newly added functions can be a single new function based on one or 
 many of the existing functions. 
 New child classes should always have the "Filter()" methods. */


#ifndef SOBELEDGE_H
#define SOBELEDGE_H


#include <iostream>
#include "BaseImage.h"
#include "NonMaxSuppression.h"


class SobelEdge : public BaseImage, public NonMaxSuppression
{
public:
	// Default constructor for usage styles not shown in main
	SobelEdge();
    SobelEdge(std::string filename);
    virtual ~SobelEdge();

	// Function overloads for different types of uses.
    virtual void Filter();
    virtual void Filter(unsigned char** input);
    virtual void Filter(unsigned char** input, int col, int row);
    void SaveEdgeMap(std::string filename);
    void SaveEdgeMap(std::string filename, int col, int row);
	unsigned char** GetEdgeMap();
    void SetThreshold(float threshold);
    float GetThreshold();
	void SaveAsOriginal(bool b);
	void SetColumns(int col);
	void SetRows(int row);
private:
    unsigned char** m_ppEdgeMap;
    long long m_lPointerOffset;
    char m_SobelOperator1[3][3];
    char m_SobelOperator2[3][3];
    float m_fThreshold;
	bool m_bSaveAsOriginal;
    int m_statistic;
};


#endif // !SOBELEDGE_H
