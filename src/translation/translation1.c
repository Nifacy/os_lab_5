#include "translation.h"
#include "convert/convert.h"


char *translation(long x)
{
    return convert_to_base(x, 2);
}
