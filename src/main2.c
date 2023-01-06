#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>


int (*gcf) (int, int) = NULL;
char* (*translation) (long) = NULL;


void *open_dynamic_library(char *filename)
{
    void *handle = dlopen(filename, RTLD_NOW);

    if(handle == NULL)
    {
        printf("[Error] OpenDynamicLibrary: Can't open library '%s'\n", filename);
        exit(1);
    }

    return handle;
}


void *get_symbol(void *handle, char *symbol)
{
    void *symb = dlsym(handle, symbol);

    if(symb == NULL)
    {
        printf("[Error] GetSymbol: Can't get symbol '%s'\n", symbol);
        exit(2);
    }

    return symb;
}


void close_library(void *handle)
{
    dlclose(handle);
}


int main()
{
    char *gcf_filenames[] = {"./libs/libgcf1.so", "./libs/libgcf2.so"};
    char *translation_filenames[] = {"./libs/libtranslation1.so", "./libs/libtranslation2.so"};

    int active_gcf = 0;
    int active_translation = 0;

    void *gcf_handle = open_dynamic_library(gcf_filenames[active_gcf]);
    void *translation_handle = open_dynamic_library(translation_filenames[active_translation]);

    gcf = get_symbol(gcf_handle, "gcf");
    translation = get_symbol(translation_handle, "translation");

    while(1)
    {
        int command_id;
        scanf("%d", &command_id);

        if(command_id == 0)
        {
            close_library(gcf_handle);
            close_library(translation_handle);

            active_gcf ^= 1;
            active_translation ^= 1;

            gcf_handle = open_dynamic_library(gcf_filenames[active_gcf]);
            translation_handle = open_dynamic_library(translation_filenames[active_translation]);
        }

        else if(command_id == 1)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            printf("Result: GCF(%d, %d) = %d\n", a, b, gcf(a, b));
        }

        else if(command_id == 2)
        {
            long x;
            scanf("%ld", &x);
            printf("Result: translation(%ld) = %s\n", x, translation(x));
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

    close_library(gcf_handle);
    close_library(translation_handle);

    printf("Program exit...\n");
    return 0;
}
