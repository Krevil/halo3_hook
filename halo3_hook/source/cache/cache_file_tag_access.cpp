#include <cache/cache_file_tag_access.h>
#include <main/main.h>

/* ---------- code */

void *tag_get(
    unsigned long group_tag,
    long index)
{
    s_cache_file_tag_instance *global_tag_instances = *main_get_module_offset<s_cache_file_tag_instance **>(0xCB3700);
    const long long k_virtual_to_physical_base_offset = *main_get_module_offset<const long long *>(0xCFEEB8);
    
    long absolute_index = index & 0xFFFF;
    long identifier = index >> 16;

    unsigned long base_address = global_tag_instances[absolute_index].base_address;

    if (base_address)
    {
        if (base_address == 0xFFFFFFFF)
        {
            return main_get_module_offset<void *>(0x73B960);
        }
        else
        {
            return (void *)(k_virtual_to_physical_base_offset + ((unsigned long long)base_address * 4));
        }
    }

    return nullptr;
}
