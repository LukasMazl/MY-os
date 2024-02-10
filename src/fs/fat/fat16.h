#ifndef FAT16_H
#define FAT16_H

#include "fs/file.h"

struct filesystem* fat16_init();

int fat16_revolve(struct disk* disk);
void* fat16_open(struct disk* disk, struct path_part* part, FILE_MODE mode);

#endif