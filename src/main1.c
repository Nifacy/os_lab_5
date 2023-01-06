#include "gcf/gcf.h"
#include "translation/translation.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    while(1)
    {
        int command_id;
        scanf("%d", &command_id);

        if(command_id == 1)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("GCF(%d, %d) = %d\n", a, b, gcf(a, b));
        }

        else if(command_id == 2)
        {
            long x;
            scanf("%ld", &x);
            printf("translation(%ld) = %s\n", x, translation(x));
        }

        else if(command_id == -1)
        {
            break;
        }
        
        else
        {
            printf("[Error] UnkownCommandId: Id %d is undefined\n", command_id);
            exit(3);
        }
    }

    printf("Program exit...\n");
    return 0;
}