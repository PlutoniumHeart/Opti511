#ifndef CONNECTEDCOMPONENTSLABELLING_H
#define CONNECTEDCOMPONENTSLABELLING_H


#include <iostream>
#include <fstream>
#include <map>
#include <climits>
#include "BaseImage.h"


// 8 connectedness
class ConnectedComponentsLabelling : public BaseImage
{
public:
    ConnectedComponentsLabelling(std::string fileName);
    ~ConnectedComponentsLabelling();

    void Filter();
    void Filter(unsigned char** input);
    void Filter(unsigned char** input, int col, int row);

    void SaveResult(std::string filename);
    void SaveResult(std::string filename, int col, int row);

    void SetColumns(int col);
    void SetRows(int row);

    void SetForeGround(unsigned char fg);
    void SetScaleToUChar(bool b);
private:
    void Reorder(unsigned char** input, int col, int row);
    void ScaleToUChar(unsigned char** input, int col, int row);
    void InverseResult(int col, int row);
private:
    unsigned char m_fg;
    bool m_bScaleUChar;
    int m_iNumOfObject;
    long long m_lPointerOffsetForResult;
    long long m_lPointerOffsetForWriting;
    float** m_ppResult;
    unsigned char** m_ppForWriting;

};


#endif // CONNECTEDCOMPONENTSLABELLING_H
