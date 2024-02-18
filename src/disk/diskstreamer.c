#include "diskstreamer.h"
#include "memory/heap/kheap.h"
#include "config.h"

#include <stdbool.h>

struct disk_stream* diskstreamer_new(int disk_id)
{
    struct disk* disk = disk_get(disk_id);
    if (!disk)
    {
        return 0;
    }

    struct disk_stream* streamer = kzalloc(sizeof(struct disk_stream));
    streamer->pps = 0;
    streamer->disk = disk;
    
    return streamer;
}

int diskstreamer_seek(struct disk_stream* stream, int pos)
{
    stream->pps = pos;
    return 0;
}

int diskstreamer_read(struct disk_stream* stream, void* out, int total)
{
    int sector = stream->pps / MYOS_SECTOR_SIZE;
    int offset = stream->pps % MYOS_SECTOR_SIZE;
    int total_to_read = total > MYOS_SECTOR_SIZE? MYOS_SECTOR_SIZE : total;
    bool overflow = (offset + total_to_read) >= MYOS_SECTOR_SIZE;
    char buf[MYOS_SECTOR_SIZE];

    if(overflow)
    {
        total_to_read -= (offset + total_to_read) - MYOS_SECTOR_SIZE;
    }

    int res = disk_read_block(stream->disk, sector, 1, buf);
    if(res < 0)
    {
        goto out;
    }
    
    for(int i = 0; i < total_to_read; i++)
    {
        *(char*)out++ = buf[offset+i];
    }

    // Adjust the stream
    stream->pps += total_to_read;
    if(overflow)
    {
        res = diskstreamer_read(stream, out, total - total_to_read);
    }
out:
    return res;
}

void diskstreamer_close(struct disk_stream* stream)
{
    kfree(stream);
}
