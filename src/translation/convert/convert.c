#include "convert.h"
#include <stdlib.h>
#include <string.h>


int __get_converted_length(long number, int base)
{
    int size;
    for(size = 0; number > 0; number /= base) size++;
    return size;
}


void __reverse(char *str)
{
    int n = strlen(str);

    for(int i = 0; i < n / 2; i++)
    {
        int j = n - i - 1;
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}


char *convert_to_base(long x, int base)
{
    int i = 0;
    int negative = 0;

    if(x < 0)
    {
        negative = 1;
        x *= -1;
    }

    int converted_length = __get_converted_length(x, base);
    char *converted = (char*) malloc(sizeof(char) * converted_length);

    while(x > 0)
    {
        converted[i] = (x % base) + '0';
        x /= base;
        i++;
    }

    if(negative)
    {
        converted[i] = '-';
        i++;
    }

    converted[i] = '\0';
    __reverse(converted);

    return converted;
}