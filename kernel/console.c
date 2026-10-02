#include "console.h"

static volatile unsigned short *const VGA = (unsigned short *)0xB8000;
static unsigned int row, col;
static unsigned char color;

void console_init(void)
{
    row = 0;
    col = 0;
    color = 0x07;
    console_clear();
}

void console_set_color(unsigned char c) { color = c; }

void console_clear(void)
{
    unsigned int i;
    for (i = 0; i < 80 * 25; ++i)
        VGA[i] = ((unsigned short)color << 8) | ' ';
    row = 0;
    col = 0;
}

void console_putc(char c)
{
    if (c == '\n') {
        col = 0;
        if (++row >= 25) row = 0;
        return;
    }
    if (c == '\r') { col = 0; return; }
    if (c == '\b') {
        if (col) {
            --col;
            VGA[row * 80 + col] = ((unsigned short)color << 8) | ' ';
        }
        return;
    }
    VGA[row * 80 + col] = ((unsigned short)color << 8) | (unsigned char)c;
    if (++col >= 80) {
        col = 0;
        if (++row >= 25) row = 0;
    }
}

void console_write(const char *s)
{
    while (*s) console_putc(*s++);
}
