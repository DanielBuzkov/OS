#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stddef.h>
#include <stdint.h>
#include "screen.h"
#include "common.h"

#define ENTER 28 //SC of Enter key
#define DELETE 14 //SC of Backscpae key

const char scanCodeToAscii[] = {
    00, //scancode 0 does not exist
    27, //01 = Esc
    49, //02 = '1'
    50, //03 = '2'
    51, //04 = '3'
    52, //05 = '4'
    53, //06 = '5'
    54, //07 = '6'
    55, //08 = '7'
    56, //09 = '8'
    57, //10 = '9'
    48, //11 = '0'
    45, //12 = '-'
    61, //13 = '='
    8,  //14 = BKSP
    9,  //15 = TAB
    113,//16 = 'q'
    119,//17 = 'w'
    101,//18 = 'e'
    114,//19 = 'r'
    116,//20 = 'i'
    121,//21 = 'y'
    117,//22 = 'u'
    105,//23 = 'i'
    111,//24 = 'o'
    112,//25 = 'p'
    91, //26 = '['
    93, //27 = ']'
    13, //28 = ENTER
    00, //29 = CTRL (does not have ascii)
    97, //30 = 'a'
    115,//31 = 's'
    100,//32 = 'd'
    102,//33 = 'f'
    103,//34 = 'g'
    104,//35 = 'h'
    106,//36 = 'j'
    107,//37 = 'k'
    108,//38 = 'l'
    59, //39 = ';'
    39, //40 = "'"
    96, //41 = '`' (~)
    00, //42 = SHIFT (does not have ascii)
    92, //43 = '\'
    122,//44 = 'z'
    120,//45 = 'x'
    99, //46 = 'c'
    118,//47 = 'v'
    98, //48 = 'b'
    110,//49 = 'n'
    109,//50 = 'm'
    44, //51 = ','
    46, //52 = '.'
    47, //53 = '/'
    00, //54 = SHIFT (does not have ascii)
    42, //55 = prt sc
    00, //56 = ALT (does not have ascii)
    32, //57 = space
    00, //58 = CAPS (does not have ascii)
    59, //59 = f1
    60, //60 = f2
    61, //61 = f3
    62, //62 = f4
    63, //63 = f5
    64, //64 = f6
    65, //65 = f7
    66, //66 = f8
    67, //67 = f9
    68, //68 = f10
    00, //69 = NUM (does not have ascii)
    00, //70 = SCROLL (does not have ascii)
    71, //71 = 7 home
    72, //72 = 8 up arrow
    73, //73 = 9 page up
    00, //74 = gray -
    75, //75 = 4 left arrow 
    00, //76 = 5 center
    77, //77 = 6 right arrow
    00, //78 = gray +
    79, //79 = 1 end
    80, //80 = 2 down arrow
    81, //81 = 3 page down
    82, //82 = 0 insert
    83  //83 = delete
};

int exit_flag = 0;

char toChar(int scanCode);
void commandHandler(char *command);
int pressed_enter(); //End Of Command
int isExit();
void exit();

#endif