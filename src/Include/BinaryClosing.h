#ifndef BINARYCLOSING_H
#define BINARYCLOSING_H


#include "BinaryOpening.h"


class BinaryClosing : public BinaryOpening
{
public:
    BinaryClosing(std::string fileName, int width);
    ~BinaryClosing();

    virtual void Filter();
    virtual void Filter(unsigned char** input);
    virtual void Filter(unsigned char** input, int col, int row);

    virtual void SaveResult(std::string fileName);
    virtual void SaveResult(std::string fileName, int col, int row);
};


#endif //BINARYCLOSING_H
