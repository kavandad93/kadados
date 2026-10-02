#include "string.h"
unsigned int kstrlen(const char*s){unsigned int n=0;while(s[n])n++;return n;}
int kstrcmp(const char*a,const char*b){while(*a&&*a==*b){a++;b++;}return(unsigned char)*a-(unsigned char)*b;}
void kstrcpy(char*d,const char*s){while((*d++=*s++));}
void kmemset(void*p,unsigned char v,unsigned int n){unsigned char*x=p;while(n--)*x++=v;}
