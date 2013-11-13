#include "BinaryOpening.h"


BinaryOpening::BinaryOpening(std::string fileName, int width)
    : BaseImage(fileName, (width%2!=0)?-(width-1)/2:0, (width%2!=0)?-(width-1)/2:0)
    , m_pDilation(NULL)
    , m_pErosion(NULL)
    , m_iBWidth(0)
{
    if(width%2 == 0 && width > 0)
    {
        std::cerr<<"Width for the structuring element is limited to be odd number."<<std::endl;
        exit(-1);
    }
    else
        m_iBWidth = width;

    m_pDilation = new BinaryDilation(m_iColumns, m_iRows, width);
    m_pErosion = new BinaryErosion(m_iColumns, m_iRows, width);
}


BinaryOpening::~BinaryOpening()
{
    if(m_pDilation!=NULL)
    {
        delete m_pDilation;
        m_pDilation = NULL;
    }
    if(m_pErosion!=NULL)
    {
        delete m_pErosion;
        m_pErosion = NULL;
    }
}


void BinaryOpening::SetForeGround(unsigned char fg)
{
    m_pDilation->SetForeGround(fg);
    m_pErosion->SetForeGround(fg);
}


void BinaryOpening::Filter()
{
    Filter(m_ppImageMatrix);
}


void BinaryOpening::Filter(unsigned char** input)
{
    Filter(input, m_iColumns, m_iRows);
}


void BinaryOpening::Filter(unsigned char** input, int col, int row)
{
    m_pErosion->Filter(m_ppImageMatrix);
    m_pDilation->Filter(m_pErosion->GetResultPointer());
}


void BinaryOpening::SaveResult(std::string fileName)
{
    SaveResult(fileName, m_iColumns, m_iRows);
}


void BinaryOpening::SaveResult(std::string fileName, int col, int row)
{
    WriteToFile(fileName, m_pDilation->GetResultPointer(), 0, 0, col, row);
}
