#include "power_off.h"


void privatePowerOff(void)
{
    outw( 0x604, 0x0 | 0x2000 );
}

