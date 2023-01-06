#include "convert/convert.h"
#include "translation.h"


char *translation(long x)
{
    return convert_to_base(x, 3);
}
