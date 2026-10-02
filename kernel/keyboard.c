#include "keyboard.h"

static const char map[128] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=', '\b','\t',
    'q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s',
    'd','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v',
    'b','n','m',',','.','/',0,'*',0,' ',0
};

static unsigned char inb(unsigned short port)
{
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static void outb(unsigned short port, unsigned char value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void keyboard_init(void)
{
    outb(0x21, 0xFD);
}

char keyboard_getchar(void)
{
    unsigned char sc;
    for (;;) {
        if (!(inb(0x64) & 1)) continue;
        sc = inb(0x60);
        if (sc & 0x80) continue;
        if (sc < sizeof(map) && map[sc]) return map[sc];
    }
}
