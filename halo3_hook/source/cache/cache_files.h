#pragma once

#include <cseries/cseries.h>
#include <tag_files/string_ids.h>

/* ---------- structures */

struct s_cache_file_tag_group
{
    tag group_tag;
    tag parent_group_tags[2];
    string_id name;
};

struct s_cache_file_tag_instance
{
    short group_index;
    short tag_index_datum_header;
    dword base_address;
};

struct s_cache_file_global_tag_index
{
    tag group_tag;
    long tag_index;
};

/* ---------- prototypes/cache_file_tag_access.cpp */

void *tag_get(tag group_tag, long index);
