
#include <cache/physical_memory_map.h>
#include <main/main.h>

/* ---------- public code */

void *physical_memory_get_address_from_virtual_address(
    dword virtual_address)
{
    const __int64 k_virtual_to_physical_base_offset = *main_get_typed_module_address<const __int64 *>(0xCFEEB8);

    if (!virtual_address)
    {
        return nullptr;
    }
    else if (virtual_address == NONE)
    {
        return main_get_typed_module_address<void *>(0x73B960);
    }

    return (void *)(k_virtual_to_physical_base_offset + ((qword)virtual_address * 4));
}
