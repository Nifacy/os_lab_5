/* Алгоритм Евклида */

#include "gcf.h"
#include <stdio.h>


int gcf(int a, int b)
{
    printf("[GCF] Using realization 1...\n");

    while(a != 0 && b != 0)
    {
        if(a > b) a %= b;
        else b %= a;
    }

    return a + b;
}
