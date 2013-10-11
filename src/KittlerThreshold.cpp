#include "KittlerThreshold.h"


KittlerThreshold::KittlerThreshold(std::string fileName)
    : BaseImage(fileName, 0, 0)
    , m_lPointerOffsetForResult(0)
    , m_ppResult(NULL)
{
    CreateHisto(m_ppImageMatrix, m_iColumns, m_iRows, UCHAR_MAX+1);
}


KittlerThreshold::~KittlerThreshold()
{
}


void KittlerThreshold::Filter()
{
    Filter(m_ppImageMatrix);
}


void KittlerThreshold::Filter(unsigned char** input)
{
    Filter(input, m_iColumns, m_iRows);
}


void KittlerThreshold::Filter(unsigned char** input, int col, int row)
{
    int i = 0, j = 0;
    double mu1Prev = 0.0, mu1 = 0.0, mu2Prev = 0.0, mu2 = 0.0,
           var1Prev = 0.0, var1 = 0.0, var2Prev = 0, var2 = 0.0, 
           q1 = 0, q2 = 0, q1Prev = 0, q2Prev = 0, mu = 0.0, H = 0.0;

    m_ppResult = (unsigned char**)BaseImage::CreateMatrix(m_iColumns, m_iRows, 0, 0, sizeof(unsigned char), &m_lPointerOffsetForResult);
    
    mu1Prev = 0.0;
    mu2Prev = Mean(1, UCHAR_MAX+1);
    mu1 = mu1Prev;
    mu2 = mu2Prev;

    for(i=0;i<=UCHAR_MAX;i++)
    {
        mu += m_dP[i]*i;
    }

    var1Prev = 0;
    var1 = 0;
    for(i=1;i<=UCHAR_MAX;i++)
    {
        var2Prev += m_dP[i]*i*i;
    }
    var2Prev -= mu2*mu2;
    var2 = var2Prev;

    q1Prev = Q(0);
    q2Prev = 1-Q(0);
    q1 = q1Prev;
    q2 = q2Prev;

    for(i=1;i<=UCHAR_MAX;i++)
    {
        q1 = Q(i);
        q2 = 1-Q(i);
        if(q1 == 0 || q2 == 0)
        {
            q1Prev = q1;
            q2Prev = q2;
            mu1Prev = mu1;
            mu2Prev = mu2;
            var1Prev = var1;
            var2Prev = var2;
            continue;
        }

        mu1 = (q1Prev*mu1Prev+i*m_dP[i])/q1;
        var1 = (q1Prev*(var1Prev+(mu1Prev-mu1)*(mu1Prev-mu1))+
                m_dP[i]*(i-mu1)*(i-mu1))/q1;

        mu2 = (mu-q1*mu1)/q2;
        var2 = (q2Prev*(var2Prev+(mu2Prev-mu2)*(mu2Prev-mu2))-
                m_dP[i]*(i-mu2)*(i-mu2))/q2;

        if(var1 <= 0 || var2 <= 0)
        {
            q1Prev = q1;
            q2Prev = q2;
            mu1Prev = mu1;
            mu2Prev = mu2;
            var1Prev = var1;
            var2Prev = var2;
            continue;
        }

        H = (q1*log(var1)+q2*log(var2))/2-q1*log(q1)-q2*log(q2);
#ifdef _DEBUG
        /*std::cout<<"Mu2Prev: "<<mu2Prev<<std::endl;
        std::cout<<"q2Prev: "<<q2Prev<<std::endl;*/
        std::cout<<i<<": "<<H<<std::endl;
#endif
        q1Prev = q1;
        q2Prev = q2;
        mu1Prev = mu1;
        mu2Prev = mu2;
        var1Prev = var1;
        var2Prev = var2;
    }
}


void KittlerThreshold::SaveResult(std::string filename)
{
    SaveResult(filename, m_iColumns, m_iRows);
}


void KittlerThreshold::SaveResult(std::string filename, int col, int row)
{
    WriteToFile(filename, m_ppResult, 0, 0, col, row);
}


void KittlerThreshold::SetColumns(int col)
{
    m_iColumns = col;
}


void KittlerThreshold::SetRows(int row)
{
    m_iRows = row;
}
