#include "ConnectedComponentsLabelling.h"


ConnectedComponentsLabelling::ConnectedComponentsLabelling(std::string fileName)
    : BaseImage(fileName, -1, -1)
    , m_lPointerOffsetForResult(0)
    , m_ppResult(NULL)
    , m_fg(0)
{
}


ConnectedComponentsLabelling::~ConnectedComponentsLabelling()
{
    if(m_ppResult != NULL)
    {
        m_ppResult += m_lPointerOffsetForResult;
        free(m_ppResult);
        m_ppResult = NULL;
    }
}


void ConnectedComponentsLabelling::Filter()
{
    Filter(m_ppImageMatrix);
}


void ConnectedComponentsLabelling::Filter(unsigned char** input)
{
    Filter(input, m_iColumns, m_iRows);
}


void ConnectedComponentsLabelling::Filter(unsigned char** input, int col, int row)
{
    int i = 0, j = 0, count = 0;
    bool changed = false;
    int marker = 1;

    m_ppResult = (long**)BaseImage::CreateMatrix(m_iColumns+2, m_iRows+2, -1, -1, sizeof(long), &m_lPointerOffsetForResult);
    for(i=-1;i<=row;i++)
    {
        for(j=-1;j<=col;j++)
        {
            m_ppResult[i][j] = 0;
        }
    }

    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            int m;
            if(input[i][j]==0)
            {
                m_ppResult[i][j] = marker++;
                m = m_ppResult[i][j];
                for(int x=-1;x<=1;x++)
                {
                    for(int y=-1;y<=1;y++)
                    {
                        if(m>m_ppResult[i+x][j+y] && m_ppResult[i+x][j+y]!=0)
                        {
                            m=m_ppResult[i+x][j+y];
                        }
                    }
                }
                if(m_ppResult[i][j]!=m)
                {
                    changed = true;
                    m_ppResult[i][j] = m;
                }
            }
        }
    }

    do
    {
        std::cout<<"Iteration count: "<<count++<<std::endl;
        changed = false;
//        marker = 1;

        // Top down, left to right
        for(i=0;i<row;i++)
        {
            for(j=0;j<col;j++)
            {
                int m;
                if(input[i][j]==0)
                {
//                    m_ppResult[i][j] = marker++;
                    m = m_ppResult[i][j];
                    for(int x=-1;x<=1;x++)
                    {
                        for(int y=-1;y<=1;y++)
                        {
                            if(m>m_ppResult[i+x][j+y] && m_ppResult[i+x][j+y]!=0)
                            {
                                m=m_ppResult[i+x][j+y];
                            }
                        }
                    }
                    if(m_ppResult[i][j]!=m)
                    {
                        changed = true;
                        m_ppResult[i][j] = m;
                    }
                }
            }
        }

        //Bottom up, right to left
        for(i=col-1;i>=0;i--)
        {
            for(j=row-1;j>=0;j--)
            {
                int m = m_ppResult[j][i];
                if(m_ppResult[j][i]!=0)
                {
                    for(int x=-1;x<=1;x++)
                    {
                        for(int y=-1;y<=1;y++)
                        {
                            if(m>m_ppResult[j+x][i+y] && m_ppResult[j+x][i+y]!=0)
                            {
                                m=m_ppResult[j+x][i+y];
                            }
                        }
                    }
                    if(m_ppResult[j][i]!=m)
                    {
                        changed = true;
                        m_ppResult[j][i] = m;
                    }
                }
            }
        }
    } while(changed);

#ifdef _DEBUG
    std::fstream debugFile;
    debugFile.open("DebugImage.txt", std::ios::out|std::ios::binary);
    if(debugFile.is_open())
    {
        for(i=0;i<m_iRows;i++)
        {
            for(j=0;j<m_iColumns;j++)
            {
                debugFile<<(int)m_ppResult[i][j]<<" ";
            }
            debugFile<<std::endl;
        }
    }
    debugFile.close();
#endif
}


void ConnectedComponentsLabelling::SaveResult(std::string filename)
{
    SaveResult(filename, m_iColumns, m_iRows);
}


void ConnectedComponentsLabelling::SaveResult(std::string filename, int col, int row)
{
//    WriteToFile(filename, m_ppResult, 0, 0, col, row);
}


void ConnectedComponentsLabelling::SetColumns(int col)
{
    m_iColumns = col;
}


void ConnectedComponentsLabelling::SetRows(int row)
{
    m_iRows = row;
}


void ConnectedComponentsLabelling::SetForeGround(unsigned char fg)
{
    m_fg = fg;
}
