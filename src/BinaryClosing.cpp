#include "BinaryClosing.h"


BinaryClosing::BinaryClosing(std::string fileName, int width)
    : BinaryOpening(fileName, width)
{
}


BinaryClosing::~BinaryClosing()
{
}


void BinaryClosing::Filter()
{
    Filter(m_ppImageMatrix);
}


void BinaryClosing::Filter(unsigned char** input)
{
    Filter(input, m_iColumns, m_iRows);
}


void BinaryClosing::Filter(unsigned char** input, int col, int row)
{
    m_pDilation->Filter(m_ppImageMatrix);
    m_pErosion->Filter(m_pDilation->GetResultPointer());
}


void BinaryClosing::SaveResult(std::string fileName)
{
    SaveResult(fileName, m_iColumns, m_iRows);
}


void BinaryClosing::SaveResult(std::string fileName, int col, int row)
{
    WriteToFile(fileName, m_pErosion->GetResultPointer(), 0, 0, col, row);
}
