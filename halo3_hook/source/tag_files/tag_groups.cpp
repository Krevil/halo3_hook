
#include <cache/physical_memory_map.h>
#include <tag_files/tag_groups.h>

/* ---------- public code */

void *tag_block_get_element_with_size(
    const s_tag_block *block,
    long index,
    long element_size)
{
    assert(block != nullptr);
    assert(block->count >= 0);

    if (!VALID_INDEX(index, block->count))
    {
        wchar_t message[256];
        swprintf_s(message, L"#%ld is not a valid %s index in [#0, #%ld]", index, L"<unknown>", block->count);
    }

    return (char *)physical_memory_get_address_from_virtual_address(block->address.m_stored) + (element_size * index);
}
