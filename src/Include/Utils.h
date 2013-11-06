#ifndef UTILS_H
#define UTILS_H


#include <climits>
#include <cstdint>

#if CHAR_BIT != 8
#error "Unsupported char size"
#endif


enum
{
    O32_LITTLE_ENDIAN = 0X03020100UL,
    O32_BIG_ENDIAN = 0X00010203UL,
    O32_PDP_ENDIAN = 0X01000302UL
};


static const union
{
    unsigned char bytes[4]; 
    uint32_t value;
} 

o32_host_order = 
{
    {0, 1, 2, 3}
};


#define O32_HOST_ORDER (o32_host_order.value)


#endif // !UTILS_H
