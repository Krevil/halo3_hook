#include <main/main.h>
#include <memory/data.h>

/* ---------- code */

long long __fastcall data_next_index(s_data_array *data, short index)
{
    return main_get_module_offset<decltype(&data_next_index)>(0x2D6B70)(data, index);
}
