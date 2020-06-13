/*
main.cpp
	the entry-point for the DLL wrapper
*/

#include <game/game_time.h>
#include <main/main.h>

#include <stddef.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

/* ---------- public globals */

s_main_globals g_main_globals = { nullptr };

/* ---------- private globals */

extern "C" IMAGE_DOS_HEADER __ImageBase;

static char g_dll_path[MAX_PATH];

/* ---------- private code */

static long long(__fastcall *lightmap_interpolation_sub_180470630)(float *, float *, float, bool) = nullptr;

long long __fastcall lightmap_interpolation_sub_180470630_hook(
	float *a1,
	float *a2,
	float a3,
	bool a4)
{
	long long ticks_per_second = game_seconds_to_ticks_round(1.0f);

	return lightmap_interpolation_sub_180470630(a1, a2, a3 / (float)((double)ticks_per_second / 30.0), true);
}

/* ---------- public code */

bool main_initialize(
	void)
{
	memset(g_dll_path, 0, sizeof(g_dll_path));
	GetModuleFileName(reinterpret_cast<HINSTANCE>(&__ImageBase), g_dll_path, sizeof(g_dll_path));

	size_t dll_path_length = strnlen_s(g_dll_path, sizeof(g_dll_path));

	if (dll_path_length > (MAX_PATH - 10))
	{
		MessageBox(nullptr, "File path for halo3_original.dll is too long!", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	memcpy_s(strstr(g_dll_path, ".dll"), 14, "_original.dll", 13);

	if (!(g_main_globals.module_address = LoadLibrary(g_dll_path)))
	{
		MessageBox(nullptr, "Failed to load halo3_original.dll!", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	if (!game_time_initialize())
	{
		MessageBox(nullptr, "Failed to initialize game time!", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	lightmap_interpolation_sub_180470630 = reinterpret_cast<decltype(lightmap_interpolation_sub_180470630)>(
		reinterpret_cast<size_t>(g_main_globals.module_address) + 0x470630);

	DetourAttach(reinterpret_cast<void **>(&lightmap_interpolation_sub_180470630), lightmap_interpolation_sub_180470630_hook);

	if (DetourTransactionCommit() != NO_ERROR)
	{
		MessageBox(nullptr, "Failed to detour functions in halo3_original.dll!", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void main_dispose(
	void)
{
	game_time_dispose();

	FreeLibrary(reinterpret_cast<HMODULE>(g_main_globals.module_address));
}

BOOL WINAPI DllMain(
	HINSTANCE instance,
	DWORD reason,
	LPVOID)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		if (!main_initialize())
			return FALSE;
		break;

	case DLL_PROCESS_DETACH:
		main_dispose();
		break;
	}

	return TRUE;
}

/* ---------- wrapper code */

extern "C" long long __stdcall CreateDataAccess(
	void *address)
{
	static decltype(CreateDataAccess) *CreateDataAccess_original = nullptr;

	if (!CreateDataAccess_original)
	{
		CreateDataAccess_original = reinterpret_cast<decltype(CreateDataAccess) *>(
			GetProcAddress(
				reinterpret_cast<HMODULE>(g_main_globals.module_address),
				"CreateDataAccess"));

		if (!CreateDataAccess_original)
		{
			MessageBox(nullptr, "Failed to load CreateDataAccess from halo3_original.dll!", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	return CreateDataAccess_original(address);
}

extern "C" long long __stdcall CreateGameEngine(
	void *address)
{
	static decltype(CreateGameEngine) *CreateGameEngine_original = nullptr;

	if (!CreateGameEngine_original)
	{
		CreateGameEngine_original = reinterpret_cast<decltype(CreateGameEngine) *>(
			GetProcAddress(
				reinterpret_cast<HMODULE>(g_main_globals.module_address),
				"CreateGameEngine"));

		if (!CreateGameEngine_original)
		{
			MessageBox(nullptr, "Failed to load CreateGameEngine from halo3_original.dll!", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	return CreateGameEngine_original(address);
}

extern "C" long long __stdcall SetLibrarySettings(
	void *address)
{
	static decltype(SetLibrarySettings) *SetLibrarySettings_original = nullptr;

	if (!SetLibrarySettings_original)
	{
		SetLibrarySettings_original = reinterpret_cast<decltype(SetLibrarySettings) *>(
			GetProcAddress(
				reinterpret_cast<HMODULE>(g_main_globals.module_address),
				"SetLibrarySettings"));

		if (!SetLibrarySettings_original)
		{
			MessageBox(nullptr, "Failed to load SetLibrarySettings from halo3_original.dll!", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}
	}

	return SetLibrarySettings_original(address);
}
