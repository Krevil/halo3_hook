
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <objects/object_hooks.h>

/* ---------- globals */

void *(__fastcall *object_try_and_get_multiplayer)(long object_index) = nullptr;

/* ---------- public code */

void object_hooks_initialize()
{
	object_try_and_get_multiplayer = main_get_module_offset<decltype(object_try_and_get_multiplayer)>(0x562CA0);
}

void object_hooks_dispose()
{
}
