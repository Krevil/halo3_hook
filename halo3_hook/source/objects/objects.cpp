
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <objects/objects.h>

/* ---------- public code */

void object_hooks_initialize()
{
}

void object_hooks_dispose()
{
}

void *object_try_and_get_and_verify_type(long object_index, dword valid_type_flags)
{
    return main_get_module_pointer_at_offset<void *(__fastcall *)(long, dword)>(0x562C50)(object_index, valid_type_flags);
}
