#ifndef K_FS_H
#define K_FS_H
#define FS_MAX 64
typedef struct{int used,dir,parent;char name[32];}FsNode;
void fs_init(void); FsNode*fs_node(int); int fs_find(int,const char*); int fs_mkdir(int,const char*);
int fs_remove(int,const char*); int fs_parent(int); int fs_is_dir(int); const char*fs_name(int);
#endif
