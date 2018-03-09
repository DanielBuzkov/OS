
#include "initrd.h"

initrd_header_t *initrd_header;     // The header.
initrd_file_header_t *file_headers; // The list of file headers.
fs_node_t initrd_root;             // Our root directory node.
fs_node_t root_nodes[3];              // List of file nodes.
int nroot_nodes;                    // Number of file nodes.

struct dirent dirent;

static uint32_t initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
    initrd_file_header_t header = file_headers[node->inode];
    if (offset > header.length)
    {
        return 0;
    }
    if (offset+size > header.length)
    {
        size = header.length-offset;
    }
    memcpy(buffer, (uint8_t*) (header.offset+offset), size);
    return size;
}

static struct dirent *initrd_readdir(fs_node_t *node, uint32_t index)
{
    if (index >= nroot_nodes)
    {
        return 0;
    }
    strcpy(dirent.name, root_nodes[index].name);
    dirent.name[strlen(root_nodes[index].name)] = 0;
    dirent.ino = root_nodes[index].inode;
    return &dirent;
}

static fs_node_t *initrd_finddir(fs_node_t *node, char *name)
{
    int i;
    for (i = 0; i < nroot_nodes; i++)
    {
        if (!strcmp(name, root_nodes[i].name))
        {
            return &root_nodes[i];
        }
    }
    return 0;
}

fs_node_t *initialise_initrd(uint32_t location)
{
    // Initialise the main and file header pointers 
    initrd_header = (initrd_header_t *)location;
    file_headers = (initrd_file_header_t *) (location+sizeof(initrd_header_t));

    // Initialise the root directory.
    strcpy(initrd_root.name, "initrd");
    initrd_root.inode = 0;
    initrd_root.length = 0;
    initrd_root.flags = FS_DIRECTORY;
    initrd_root.read = 0;
    initrd_root.readdir = &initrd_readdir;
    initrd_root.finddir = &initrd_finddir;

    nroot_nodes = initrd_header->nfiles;

    // For every file
    int i;
    for (i = 0; i < initrd_header->nfiles; i++)
    {
        // Edit the file's header so the offset will be relative to the start
        // of memory.
        file_headers[i].offset += location;
        // Create a new file node.
        strcpy(root_nodes[i].name, &file_headers[i].name);
        root_nodes[i].length = file_headers[i].length;
        root_nodes[i].inode = i;
        root_nodes[i].flags = FS_FILE;
        root_nodes[i].read = &initrd_read;
        root_nodes[i].readdir = 0;
        root_nodes[i].finddir = 0;
    }
    return &initrd_root;
}
