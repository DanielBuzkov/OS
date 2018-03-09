
#ifndef FS_H
#define FS_H

#include "common.h"

#define FS_FILE        0x01
#define FS_DIRECTORY   0x02

struct fs_node;

// These typedefs define the type of callbacks - called when read/write/open/close
// are called.
typedef uint32_t (*read_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);

typedef struct dirent * (*readdir_type_t)(struct fs_node*,uint32_t);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name);

typedef void (*exec_type_t)(struct fs_node*);

typedef struct fs_node
{
    char name[128];     // The filename
    uint32_t flags;       // Includes the node type
    uint32_t inode;       // provides a way for a filesystem to identify files
    uint32_t length;
    read_type_t read;
    readdir_type_t readdir;
    finddir_type_t finddir;
} fs_node_t;

struct dirent
{
    char name[128]; // Filename
    uint32_t ino;     // Inode number
};


extern fs_node_t *fs_root; // The root of the filesystem



uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, char *buffer);

struct dirent *readdir_fs(fs_node_t *node, uint32_t index);
fs_node_t *finddir_fs(fs_node_t *node, char *name);

#endif
