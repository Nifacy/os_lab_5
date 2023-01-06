/* Наивный алгоритм */

#include "gcf.h"
#include <stdio.h>


int gcf(int a, int b)
{
    printf("[GCF] Using realization 2...\n");

    int m = (a < b) ? a : b;

    while(m > 1)
    {
        if(a % m == 0 && b % m == 0)
            return m;

        m--;
    }

    return 1;
}
