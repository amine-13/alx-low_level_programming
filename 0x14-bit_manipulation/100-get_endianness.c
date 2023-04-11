#include "main.h"

 *
 * Return: 0 si big endian, 1 si little endian
 */
int get_endianness(void)
{
    unsigned int x = 1;
    char *c = (char *) &x;

    if (*c)
        return 1;
    else
        return 0;
}


