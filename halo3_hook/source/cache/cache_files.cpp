
#include <cache/cache_files.h>
#include <main/main.h>

/* ---------- code */

void *tag_get(
    tag /* group_tag */,
    long index)
{
    s_cache_file_tag_instance *global_tag_instances = *main_get_from_module_offset<s_cache_file_tag_instance **>(0xCB3700);
    const __int64 k_virtual_to_physical_base_offset = *main_get_from_module_offset<const __int64 *>(0xCFEEB8);
    
    dword base_address = global_tag_instances[index & 0xFFFF].base_address;

    if (base_address)
    {
        if (base_address == 0xFFFFFFFF)
        {
            return main_get_from_module_offset<void *>(0x73B960);
        }
        else
        {
            return (void *)(k_virtual_to_physical_base_offset + ((qword)base_address * 4));
        }
    }

    return nullptr;
}
