
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

void *object_try_and_get_multiplayer(long object_index)
{
	return main_get_from_module_offset<void *(*)(long)>(0x562CA0)(object_index);
}
