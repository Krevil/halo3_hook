#pragma once

#include <cseries/cseries.h>
#include <tag_files/tag_group_access.h>

/* ---------- prototypes/tag_groups.cpp */

void *tag_block_get_element_with_size(
	const s_tag_block *block,
	long index,
	long element_size);
