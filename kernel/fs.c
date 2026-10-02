#include "fs.h"
#include "string.h"
static FsNode n[FS_MAX];
FsNode*fs_node(int x){return x>=0&&x<FS_MAX&&n[x].used?&n[x]:0;}
int fs_parent(int x){return fs_node(x)?n[x].parent:0;}
int fs_is_dir(int x){return fs_node(x)?n[x].dir:0;}
const char*fs_name(int x){return fs_node(x)?n[x].name:"";}
int fs_find(int p,const char*s){int i;for(i=0;i<FS_MAX;i++)if(n[i].used&&n[i].parent==p&&!kstrcmp(n[i].name,s))return i;return-1;}
static int add(int p,const char*s,int d){int i;if(!fs_node(p)||!n[p].dir||!s[0]||fs_find(p,s)>=0)return-1;for(i=1;i<FS_MAX;i++)if(!n[i].used){n[i].used=1;n[i].dir=d;n[i].parent=p;kstrcpy(n[i].name,s);return i;}return-1;}
int fs_mkdir(int p,const char*s){return add(p,s,1);}
int fs_remove(int p,const char*s){int x=fs_find(p,s),i;if(x<1)return-1;if(n[x].dir)for(i=0;i<FS_MAX;i++)if(n[i].used&&n[i].parent==x)return-2;n[x].used=0;return 0;}
void fs_init(void){int h;kmemset(n,0,sizeof n);n[0].used=1;n[0].dir=1;n[0].parent=0;kstrcpy(n[0].name,"/");h=fs_mkdir(0,"home");if(h>=0)fs_mkdir(h,"kavan");}
