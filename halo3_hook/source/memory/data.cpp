
#include <main/main.h>
#include <memory/data.h>

/* ---------- code */

long data_next_index(s_data_array *data, long index)
{
    return (long)main_get_module_pointer_at_offset<__int64(__fastcall *)(s_data_array *, short)>(0x2D6B70)(data, (short)(index & 0xFFFF));
}

void *datum_try_and_get(const s_data_array *data, long index)
{
    return main_get_module_pointer_at_offset<void *(__fastcall *)(const s_data_array *, long)>(0x2D71A0)(data, index);
}
