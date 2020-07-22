
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <render/render_objects.h>

/* ---------- globals */

static bool g_render_objects_motion_blur_enabled = true;

/* ---------- prototypes */

static void __fastcall render_objects_prepare_for_window(long user_index);
static decltype(render_objects_prepare_for_window) *render_objects_prepare_for_window__original = nullptr;

/* ---------- public code */

void render_object_hooks_initialize()
{
	render_objects_prepare_for_window__original = main_get_typed_module_address<decltype(render_objects_prepare_for_window__original)>(0x472000);

	DetourAttach((PVOID *)&render_objects_prepare_for_window__original, render_objects_prepare_for_window);
}

void render_object_hooks_dispose()
{
	DetourDetach((PVOID *)&render_objects_prepare_for_window__original, render_objects_prepare_for_window);
}

bool render_objects_motion_blur_enabled()
{
	return g_render_objects_motion_blur_enabled;
}

void render_objects_set_motion_blur_enabled(bool enabled)
{
	g_render_objects_motion_blur_enabled = enabled;
}

/* ---------- private code */

void __fastcall render_objects_prepare_for_window(long user_index)
{
	render_objects_prepare_for_window__original(user_index);

	if (!g_render_objects_motion_blur_enabled)
	{
		bool *g_motion_blur_enabled = main_get_typed_module_address<bool *>(0x8FD910);

		*g_motion_blur_enabled = false;
	}
}
