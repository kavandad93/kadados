#include "shell.h"
#include "console.h"
#include "keyboard.h"
#include "fs.h"
#include "string.h"
static int cwd=0;static char line[128];
static void prompt(void){console_write("kavan@Kadad--kavan ");if(!cwd)console_write("/");else{int a[16],m=0,x=cwd,i;while(x&&m<16){a[m++]=x;x=fs_parent(x);}for(i=m-1;i>=0;i--){console_putc('/');console_write(fs_name(a[i]));}console_putc('/');}console_write(" >_");}
static void arg(const char*s,char*d){int i=0;while(s[i]&&s[i]!=' '&&i<31){d[i]=s[i];i++;}d[i]=0;}
static void ls(void){int i;for(i=0;i<FS_MAX;i++){FsNode*x=fs_node(i);if(x&&x->parent==cwd){console_set_color(x->dir?0x0B:0x07);console_write(x->name);if(x->dir)console_putc('/');console_set_color(7);console_putc(' ');}}console_putc('\n');}
static void exec(char*c){char a[32];int x;if(!c[0])return;if(!kstrcmp(c,"help"))console_write("nano ls dir mkdir rm rmdir cd pwd clear echo help\n");else if(!kstrcmp(c,"ls")||!kstrcmp(c,"dir"))ls();else if(!kstrcmp(c,"pwd")){console_write(cwd?"/home/kavan/\n":"/\n");}else if(!kstrcmp(c,"clear"))console_clear();else if(!kstrncmp(c,"echo ",5)){console_write(c+5);console_putc('\n');}else if(!kstrncmp(c,"mkdir ",6)){arg(c+6,a);console_write(fs_mkdir(cwd,a)>=0?"Directory created.\n":"mkdir: cannot create directory\n");}else if(!kstrncmp(c,"rm ",3)){arg(c+3,a);console_write(fs_remove(cwd,a)==0?"Removed.\n":"rm: cannot remove\n");}else if(!kstrncmp(c,"rmdir ",6)){arg(c+6,a);x=fs_find(cwd,a);console_write(x>=0&&fs_is_dir(x)&&fs_remove(cwd,a)==0?"Directory removed.\n":"rmdir: directory not empty or not found\n");}else if(!kstrcmp(c,"cd"))cwd=0;else if(!kstrncmp(c,"cd ",3)){arg(c+3,a);if(!kstrcmp(a,".."))cwd=fs_parent(cwd);else{x=fs_find(cwd,a);if(x>=0&&fs_is_dir(x))cwd=x;else console_write("cd: directory not found\n");}}else if(!kstrcmp(c,"nano"))console_write("nano: editor pending persistent filesystem support.\n");else console_write("command not found\n");}
void shell_run(void){unsigned int l=0;char c;for(;;){prompt();for(;;){c=keyboard_getchar();if(c=='\n'){line[l]=0;console_putc('\n');exec(line);l=0;break;}if(c=='\b'){if(l){l--;console_putc('\b');}continue;}if(l<127){line[l++]=c;console_putc(c);}}}}
