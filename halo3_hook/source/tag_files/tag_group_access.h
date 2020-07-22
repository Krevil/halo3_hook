#pragma once

#include <cseries/cseries.h>

/* ---------- structures */

struct s_tag_group {};

struct s_tag_block_definition {};

struct s_tag_block
{
    long count;
    ptr32_t<void> address;
    ptr32_t<const s_tag_block_definition> definition;
};

struct s_tag_data_definition {};

struct s_tag_data
{
    long size;
    unsigned long internal_flags;
    unsigned long file_position;
    ptr32_t<void> address;
    ptr32_t<const s_tag_data_definition> definition;
};

struct s_tag_reference
{
    tag group_tag;
    ptr32_t<const char> name;
    long name_length;
    long index;
};

struct s_tag_resource_definition {};

struct s_tag_resource
{
    long resource_handle;
    ptr32_t<const s_tag_resource_definition> definition;
};

struct s_tag_interop_definition {};

struct s_tag_interop
{
    ptr32_t<void> descriptor;
    ptr32_t<void> address;
    ptr32_t<const s_tag_interop_definition> definition;
};
