/* Base class, mainly handle image I/O and other common operations*/


#ifndef BASEIMAGE_H
#define BASEIMAGE_H


#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>


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


class BaseImage
{
public:
    BaseImage(std::string filename, int startCol, int startRow);
    BaseImage(int col, int row, int startCol, int startRow);
    virtual ~BaseImage();

    static void** CreateMatrix(int col, int row, int startCol, int startRow, int element_size, long long* offset);
    template<typename T> static void Reflect(int col, int row, int amount, T** input);
    void WriteToFile(std::string filename, unsigned char** input, int startCol, int startRow, int col, int row);
    unsigned char** GetImagePointer();
    int GetColumns();
    int GetRows();
protected:
    std::string m_Filename;
    std::fstream m_ImageFile;
    int m_iColumns;
    int m_iRows;
    int m_iBpp;
    unsigned char** m_ppImageMatrix;
private:
    int ReadHeader(int MaxValue);
private:
    long long m_lPointerOffset; // Used to keep track of the pointer to the 2D array.
};

template<typename T>
void BaseImage::Reflect(int col, int row, int amount, T** input)
{
    int i = 0, j = 0;

    if(amount<1 || amount>(row+1)/2 || amount>(col+1)/2)
    {
        throw std::invalid_argument("Image Columns and Rows must be larger than 0.");
    }

    for(i=-amount;i<0;i++)
    {
        for(j=-amount;j<0;j++)
        {
            input[i][j] = input[-i-1][-j-1];
        }
        for(j=0;j<col;j++)
        {
            input[i][j] = input[-i-1][j];
        }
        for(j=col;j<col+amount;j++)
        {
            input[i][j] = input[-i-1][col*2-j-1];
        }
    }

    for(i=0;i<row;i++)
    {
        for(j=-amount;j<0;j++)
        {
            input[i][j] = input[i][-j-1];
        }
        for(j=col;j<col+amount;j++)
        {
            input[i][j] = input[i][col*2-j-1];
        }
    }

    for(i=row;i<row+amount;i++)
    {
        for(j=-amount;j<0;j++)
        {
            input[i][j] = input[row*2-i-1][-j-1];
        }
        for(j=0;j<col;j++)
        {
            input[i][j] = input[row*2-i-1][j];
        }
        for(j=col;j<col+amount;j++)
        {
            input[i][j] = input[row*2-i-1][col*2-j-1];
        }
    }
}


#endif // !BASEIMAGE_H
