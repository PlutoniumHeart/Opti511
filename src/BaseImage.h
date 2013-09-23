/* Base class, mainly handle image I/O and other common operations*/


#ifndef BASEIMAGE_H
#define BASEIMAGE_H


#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>


class BaseImage
{
public:
	BaseImage();
	BaseImage(std::string filename, int startCol, int startRow);
	virtual ~BaseImage();

    static void** CreateMatrix(int col, int row, int startCol, int startRow, int element_size, long long* offset);
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
protected:
    void Reflect(int amount);
private:
	int ReadHeader(int MaxValue);
private:
    long long m_lPointerOffset; // Used to keep track of the pointer to the 2D array.
};


#endif // !BASEIMAGE_H
