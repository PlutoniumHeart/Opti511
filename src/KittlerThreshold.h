#ifndef KITTLERTHRESHOLD_H
#define KITTLERTHRESHOLD_H


#include "Histogram.h"
#include "BaseImage.h"


class KittlerThreshold : public BaseImage, public Histogram
{
public:
    KittlerThreshold(std::string fileName);
    ~KittlerThreshold();
};


#endif // !KITTLERTHRESHOLD_H
