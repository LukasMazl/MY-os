#ifndef DISK_H
#define DISK_H

typedef unsigned int MYOS_DISK_TYPE;

// Represent a real physical hard disk
#define MYOS_DISK_TYPE_REAL 0

struct disk
{
    MYOS_DISK_TYPE type;
    int sector_size;
};

void disk_search_and_init();
struct disk* disc_get(int index);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);

#endif