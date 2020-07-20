
#include <stddef.h>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <main/main.h>
#include <math/color_math.h>
#include <memory/data.h>
#include <cache/cache_files.h>
#include <effects/screen_effects.h>

/* ---------- prototypes */

static void __fastcall screen_effect_sample(const real_point3d *, const real_vector3d *, void *, long);
static decltype(screen_effect_sample) *screen_effect_sample__original = nullptr;

/* ---------- public code */

void screen_effect_hooks_initialize()
{
	screen_effect_sample__original = main_get_module_offset<decltype(screen_effect_sample__original)>(0x377C40);

	DetourAttach((PVOID *)&screen_effect_sample__original, screen_effect_sample);
}

void screen_effect_hooks_dispose()
{
	DetourDetach((PVOID *)&screen_effect_sample__original, screen_effect_sample);
}

/* ---------- private code */

static void __fastcall screen_effect_sample(
	const real_point3d *sample_position,
	const real_vector3d *sample_forward,
	void *screen_effect_settings,
	long first_person_user_index)
{
	if (!screen_effect_settings)
	{
		return;
	}

	memset(screen_effect_settings, 0, 0x38);

	set_real_linear_rgb_color((real_linear_rgb_color *)((char *)screen_effect_settings + 0x20), 1.0f, 1.0f, 1.0f);
	set_real_linear_rgb_color((real_linear_rgb_color *)((char *)screen_effect_settings + 0x2C), 0.0f, 0.0f, 0.0f);

	s_data_array *screen_effects = *main_get_tls_offset<s_data_array **>(0x210);

	for (long i = data_next_index(screen_effects, -1); i != -1; i = data_next_index(screen_effects, i))
	{
		void *datum = (char *)screen_effects->data + ((size_t)screen_effects->size * (i & 0xFFFF));
		void *definition = tag_get('sefc', *(long *)((char *)datum + 0x4));

		//
		// TODO: finish
		//

		continue;
	}

	screen_effect_sample__original(sample_position, sample_forward, screen_effect_settings, first_person_user_index);
}
