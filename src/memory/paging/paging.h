#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>

#define PAGING_CASHE_DISABLED   0b0010000
#define PAGING_WRITE_THROUGHT   0b0001000
#define PAGING_ACCESS_FROM_ALL  0b0000100
#define PAGING_IS_WRITEABLE     0b0000010
#define PAGING_IS_PRESENT       0b0000001


#define PAGING_TOTAL_ENTRIES_PER_TABLE  1024
#define PAGING_PAGE_SIZE                4096

struct paging_4gb_chunk
{
    uint32_t* directory_entry;
};

struct paging_4gb_chunk* paging_new_4gb(uint8_t flags);
void page_switch(uint32_t* directory);
void enable_paging();

uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk);

#endif