#ifndef FAT16_H
#define FAT16_H

#include "fs/file.h"

struct filesystem* fat16_init();

int fat16_resolve(struct disk* disk);
void* fat16_open(struct disk* disk, struct path_part* path, FILE_MODE mode);
int fat16_read(struct disk* disk, void* private, uint32_t size, uint32_t unmemb, char* out);

#endif