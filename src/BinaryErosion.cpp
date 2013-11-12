#include "BinaryErosion.h"


BinaryErosion::BinaryErosion(std::string fileName, int width)
    : BaseImage(fileName, (width%2!=0)?-(width-1)/2:0, (width%2!=0)?-(width-1)/2:0)
    , m_iBWidth(0)
    , m_ppResult(NULL)
    , m_lPointerOffsetForResult(0)
    , m_fg(0)
{
    if(width%2 == 0 && width > 0)
    {
        std::cerr<<"Width for the structuring element is limited to be odd number."<<std::endl;
        exit(-1);
    }
    else
        m_iBWidth = width;
}


BinaryErosion::~BinaryErosion()
{
    if(m_ppResult!=NULL)
    {
        m_ppResult += m_lPointerOffsetForResult;
        free(m_ppResult);
        m_ppResult = NULL;
    }
}


void BinaryErosion::SetForeGround(unsigned char fg)
{
    if(fg>0)
        m_fg = 255;
    else
        m_fg = 0;
}


void BinaryErosion::Filter()
{
    Filter(m_ppImageMatrix);
}


void BinaryErosion::Filter(unsigned char** input)
{
    Filter(input, m_iColumns, m_iRows);
}


void BinaryErosion::Filter(unsigned char** input, int col, int row)
{
    int i = 0, j = 0;
    int x = 0, y = 0;
    m_ppResult = (unsigned char**)BaseImage::CreateMatrix(m_iColumns+m_iBWidth-1, m_iRows+m_iBWidth-1, -(m_iBWidth-1)/2, -(m_iBWidth-1)/2, sizeof(unsigned char), &m_lPointerOffsetForResult);

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            m_ppResult[i][j] = m_fg;
        }
    }
    
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            if(input[i][j]==255-m_fg)
            {
                for(x=-(m_iBWidth-1)/2;x<(m_iBWidth-1)/2;x++)
                {
                    for(y=-(m_iBWidth-1)/2;y<(m_iBWidth-1)/2;y++)
                    {
                        m_ppResult[i+x][j+y] = 255-m_fg;
                    }
                }
            }
        }
    }
}


void BinaryErosion
::SaveResult(std::string fileName)
{
    SaveResult(fileName, m_iColumns, m_iRows);
}


void BinaryErosion::SaveResult(std::string fileName, int col, int row)
{
    WriteToFile(fileName, m_ppResult, 0, 0, col, row);
}
