#ifndef KADADOS_CONSOLE_H
#define KADADOS_CONSOLE_H

void console_init(void);
void console_clear(void);
void console_write(const char *s);
void console_putc(char c);
void console_set_color(unsigned char color);

#endif
