
#include <cache/cache_files.h>
#include <cache/physical_memory_map.h>
#include <main/main.h>

/* ---------- code */

void *tag_get(
    tag /* group_tag */,
    long index)
{
    if (index == NONE)
    {
        return nullptr;
    }

    s_cache_file_tag_instance *global_tag_instances = *main_get_typed_module_address<s_cache_file_tag_instance **>(0xCB3700);

    return physical_memory_get_address_from_virtual_address(global_tag_instances[index & 0xFFFF].base_address);
}
