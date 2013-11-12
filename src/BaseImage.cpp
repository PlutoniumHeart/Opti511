#include "BaseImage.h"


// Constructor used for loading image
BaseImage::BaseImage(std::string filename, int startCol, int startRow)
    : m_iColumns(0)
    , m_iRows(0)
    , m_iBpp(0)
    , m_ppImageMatrix(NULL)
    , m_lPointerOffset(0)
{
    if(filename.size() == 0)
    {
        throw std::invalid_argument("No file name specified. ");
    }
    else
    {
        m_Filename = filename;
    }
    m_ImageFile.open(filename.c_str(), std::ios::in|std::ios::binary);
    if(m_ImageFile.is_open())
    {
        if(ReadHeader(255) < 0)
        {
            return;
        }
        m_ppImageMatrix = (unsigned char**)CreateMatrix(m_iColumns+2*(startCol<0 ? -startCol : 0), m_iRows+2*(startRow<0 ? -startRow : 0), startCol, startRow, sizeof(unsigned char), &m_lPointerOffset);
        if(m_ppImageMatrix == NULL)
        {
            std::cerr<<"Failed to allocate memory."<<std::endl;
            return;
        }
        for(int i=0;i<m_iRows;i++)
        {
            m_ImageFile.read((char*)&m_ppImageMatrix[i][0], m_iColumns);
        }
        if(startCol!=0)
        {
            Reflect<unsigned char>(m_iColumns, m_iRows, std::abs(startCol), m_ppImageMatrix);
        }
    }
    else
    {
        std::cerr<<"Unable to open file!"<<std::endl;
        exit(-1);
    }
    m_ImageFile.close();
}


BaseImage::~BaseImage()
{
    if(m_ppImageMatrix!=NULL)
    {
        m_ppImageMatrix += m_lPointerOffset;
        free(m_ppImageMatrix);
        m_ppImageMatrix = NULL;
    }
}


int BaseImage::ReadHeader(int MaxValue)
{
    std::string line;
    
    std::getline(m_ImageFile, line);
    while(*line.begin() == '#')
    {
        std::getline(m_ImageFile, line);
    }
    
    if(*line.begin() != 'P' || *(line.begin()+1) != '5')
    {
        std::cerr<<"File is not supported."<<std::endl;
        return -1;
    }
    
    std::getline(m_ImageFile, line);
    while(*line.begin() == '#')
    {
        std::getline(m_ImageFile, line);
    }
    std::stringstream ss(line);
    if(!(ss>>m_iColumns>>m_iRows))
    {
        std::cerr<<"Column number or Row number not recognized."<<std::endl;
        return -1;
    }
    ss.str(std::string());
    ss.clear();
    
    std::getline(m_ImageFile, line);
    while(*line.begin() == '#')
    {
        std::getline(m_ImageFile, line);
    }
    ss<<line;
    if(!(ss>>m_iBpp))
    {
        std::cerr<<"Bpp value is not recognized."<<std::endl;
        return -1;
    }
    if(m_iBpp>MaxValue)
    {
        std::cerr<<"Bad bpp value."<<std::endl;
        return -1;
    }
    return 0;
}


void** BaseImage::CreateMatrix(int col, int row, int startCol, int startRow, int element_size, long long* offset)
{
    void **p;
    void **temp;
    int alignment = 0;
    long i = 0;
    
    if(col<1 || row<1)
    {
        throw std::invalid_argument("Image Columns and Rows must be larger than 0.");
    }
    
    i = row*sizeof(void *);
    alignment = i%sizeof(long double);
    if(alignment != 0)
    {
        alignment = sizeof(long double) - alignment;
    }
    
    i+= row*col*element_size+alignment;
    if((p = (void **)malloc((size_t)i)) != NULL)
    {
        temp = p;
        p[0] = (char*)(p+row) + alignment - startCol*element_size;
        for(i=1;i<row;i++)
        {
            p[i] = (char*)(p[i-1])+col*element_size;
        }
        p-=startRow;
    }
    *offset = temp-p;
    return (p);
}


void BaseImage::WriteToFile(std::string filename, unsigned char** input, int startCol, int startRow, int col, int row)
{
    std::fstream file(filename.c_str(), std::ios::out|std::ios::binary);
    if(file.is_open())
    {
        file<<"P5"<<std::endl;
        file<<col<<" "<<row<<std::endl;
        file<<"255"<<std::endl;
        for(int i=startRow;i<m_iRows+std::abs(startCol);i++)
        {
            file.write((char*)&input[i][startCol], col);
        }
    }
    else
    {
        std::cerr<<"Unable to open file to write!"<<std::endl;
        return;
    }
    file.close();
}


unsigned char** BaseImage::GetImagePointer()
{
    return m_ppImageMatrix;
}


int BaseImage::GetColumns()
{
    return m_iColumns;
}


int BaseImage::GetRows()
{
    return m_iRows;
}
