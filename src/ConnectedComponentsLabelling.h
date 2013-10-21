#ifndef CONNECTEDCOMPONENTSLABELLING_H
#define CONNECTEDCOMPONENTSLABELLING_H


#include <iostream>
#include <fstream>
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
private:
    void Reorder();
private:
    unsigned char m_fg;
    long long m_lPointerOffsetForResult;
    long** m_ppResult;
};


#endif // CONNECTEDCOMPONENTSLABELLING_H
