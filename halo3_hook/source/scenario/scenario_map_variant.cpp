
#include <main/main.h>
#include <scenario/scenario_map_variant.h>

/* ---------- public code */

void *__fastcall game_engine_get_runtime_map_variant()
{
    return main_get_typed_module_address<decltype(&game_engine_get_runtime_map_variant)>(0x269570)();
}
