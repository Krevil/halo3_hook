
#include <cache/physical_memory_map.h>
#include <main/main.h>

/* ---------- public code */

void *physical_memory_get_address_from_virtual_address(
    dword virtual_address)
{
    const long long k_virtual_to_physical_base_offset = *main_get_typed_module_address<const long long *>(0x1AB9BA8);

    if (!virtual_address)
    {
        return nullptr;
    }

    return (void *)(k_virtual_to_physical_base_offset + ((qword)virtual_address * 4));
}
