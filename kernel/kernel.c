#include "console.h"
#include "keyboard.h"
#include "fs.h"
#include "shell.h"

void kernel_main(unsigned long magic, unsigned long mbi)
{
    (void)magic;
    (void)mbi;

    console_init();
    fs_init();
    keyboard_init();

    console_write("KadadOS kernel initialized.\n");
    console_write("VPS mode: SSH userspace will attach to the Kadad shell when networking is available.\n\n");

    shell_run();

    for (;;) {
        __asm__ volatile ("hlt");
    }
}
