#pragma once

/* ---------- structures */

struct s_cache_file_tag_instance
{
    short group_index;
    short tag_index_datum_header;
    unsigned long base_address;
};
static_assert(sizeof(s_cache_file_tag_instance) == 0x8);

/* ---------- prototypes/cache_file_tag_access.cpp */

void *tag_get(unsigned long group_tag, long index);
