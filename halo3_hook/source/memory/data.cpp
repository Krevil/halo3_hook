#include <main/main.h>
#include <memory/data.h>

/* ---------- code */

long data_next_index(s_data_array *data, long index)
{
    return (long)main_get_module_offset<__int64(*)(s_data_array *, short)>(0x2D6B70)(data, (short)(index & 0xFFFF));
}
