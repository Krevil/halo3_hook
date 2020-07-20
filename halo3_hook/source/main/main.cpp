/*
main.cpp
	the entry-point for the DLL wrapper
*/

#include <assert.h>
#include <stddef.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winternl.h>
#include <detours.h>

#include <game/game.h>
#include <game/game_engine_sandbox.h>
#include <input/input.h>
#include <main/main.h>
#include <objects/lights.h>
#include <objects/objects.h>
#include <effects/screen_effects.h>
#include <physics/havok_component.h>
#include <scenario/scenario.h>
#include <scenario/scenario_kill_trigger_volumes.h>
#include <scenario/scenario_soft_ceilings.h>

/* ---------- structures */

struct s_main_globals
{
	bool initialized;
	void *base_address;
	void *module_address;
};

/* ---------- globals */

static s_main_globals main_globals
{
	.initialized = false,
	.base_address = nullptr,
	.module_address = nullptr
};

/* ---------- prototypes */

static bool main_initialize_globals(void *base_address);

static bool main_initialize_detours();
static void main_dispose_detours();

/* ---------- public code */

bool main_initialize(void *base_address)
{
	return main_initialize_globals(base_address)
		&& main_initialize_detours();
}

void main_dispose()
{
	if (!main_globals.initialized)
	{
		return;
	}

	main_dispose_detours();

	FreeLibrary(reinterpret_cast<HMODULE>(main_globals.module_address));

	main_globals.initialized = false;
}

bool main_initialized()
{
	return main_globals.initialized;
}

void *main_get_base_address()
{
	assert(main_initialized());
	return main_globals.base_address;
}

void *main_get_module_address()
{
	assert(main_initialized());
	return main_globals.module_address;
}

void *main_get_tls_address()
{
	assert(main_initialized());

	__int64 tls_index = *main_get_module_offset<long *>(0x9F219C);

	return *(void **)(__readgsqword(0x58u) + (8 * tls_index));
}

/* ---------- private code */

static bool main_initialize_globals(void *base_address)
{
	if (main_initialized())
	{
		return true;
	}

	static char dll_path[MAX_PATH];
	memset(dll_path, 0, sizeof(dll_path));

	GetModuleFileName(reinterpret_cast<HINSTANCE>(base_address), dll_path, sizeof(dll_path));

	size_t dll_path_length = strnlen_s(dll_path, sizeof(dll_path));

	if (dll_path_length > (MAX_PATH - 10))
	{
		MessageBox(nullptr, "File path for original module is too long!", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	memcpy_s(strstr(dll_path, ".dll"), 14, "_original.dll", 13);

	if (!(main_globals.module_address = LoadLibrary(dll_path)))
	{
		MessageBox(nullptr, "Failed to load original module!", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	main_globals.initialized = true;

	return true;
}

static bool main_initialize_detours()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	game_hooks_initialize();
	game_engine_sandbox_hooks_initialize();
	input_hooks_initialize();
	light_hooks_initialize();
	object_hooks_initialize();
	screen_effect_hooks_initialize();
	havok_component_hooks_initialize();
	scenario_hooks_initialize();
	scenario_kill_trigger_volume_hooks_initialize();
	scenario_soft_ceiling_hooks_initialize();

	return DetourTransactionCommit() == NO_ERROR;
}

void main_dispose_detours()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	scenario_soft_ceiling_hooks_dispose();
	scenario_kill_trigger_volume_hooks_dispose();
	scenario_hooks_dispose();
	havok_component_hooks_dispose();
	screen_effect_hooks_dispose();
	object_hooks_dispose();
	light_hooks_dispose();
	input_hooks_dispose();
	game_engine_sandbox_hooks_dispose();
	game_hooks_dispose();

	DetourTransactionCommit();
}

/* ---------- wrapper code */

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID)
{

	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		if (!main_initialize(reinterpret_cast<void *>(instance)))
			return FALSE;
		break;

	case DLL_PROCESS_DETACH:
		main_dispose();
		break;
	}

	return TRUE;
}

extern "C" __int64 __stdcall CreateDataAccess(void *address)
{
	static decltype(CreateDataAccess) *CreateDataAccess_original = nullptr;

	if (!CreateDataAccess_original)
	{
		CreateDataAccess_original = (decltype(&CreateDataAccess))GetProcAddress((HMODULE)main_globals.module_address, "CreateDataAccess");

		if (!CreateDataAccess_original)
		{
			MessageBox(nullptr, "Failed to load CreateDataAccess from original module!", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	return CreateDataAccess_original(address);
}

extern "C" __int64 __stdcall CreateGameEngine(void *address)
{
	static decltype(CreateGameEngine) *CreateGameEngine_original = nullptr;

	if (!CreateGameEngine_original)
	{
		CreateGameEngine_original = (decltype(&CreateGameEngine))GetProcAddress((HMODULE)main_globals.module_address, "CreateGameEngine");

		if (!CreateGameEngine_original)
		{
			MessageBox(nullptr, "Failed to load CreateGameEngine from original module!", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	return CreateGameEngine_original(address);
}

extern "C" __int64 __stdcall SetLibrarySettings(void *address)
{
	static decltype(SetLibrarySettings) *SetLibrarySettings_original = nullptr;

	if (!SetLibrarySettings_original)
	{
		SetLibrarySettings_original = (decltype(&SetLibrarySettings))GetProcAddress((HMODULE)main_globals.module_address, "SetLibrarySettings");

		if (!SetLibrarySettings_original)
		{
			MessageBox(nullptr, "Failed to load SetLibrarySettings from original module!", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	return SetLibrarySettings_original(address);
}
