
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <detours.h>

#include <game/game.h>
#include <game/game_engine_sandbox.h>
#include <input/input.h>
#include <interface/chud/chud_messaging.h>
#include <main/main.h>
#include <simulation/simulation_history.h>

/* ---------- constants */

enum
{
	k_map_variant_data_size = 0xE090
};

/* ---------- classes */

class c_simulation_history_map_variant_action :
	public c_simulation_history_action
{
public:
	c_simulation_history_map_variant_action(const wchar_t *description, void *address);

	const wchar_t *get_description() const;
	void apply();

private:
	const wchar_t *m_description;
	char m_map_variant_data[k_map_variant_data_size];
};

/* ---------- globals */

static c_simulation_history_manager g_history_manager;

/* ---------- prototypes */

static bool __fastcall c_sandbox_engine__initialize_for_new_map(void *engine, void *);
static decltype(c_sandbox_engine__initialize_for_new_map) *c_sandbox_engine__initialize_for_new_map__original = nullptr;

static void __fastcall c_sandbox_engine__update(void *engine, void *);
static decltype(c_sandbox_engine__update) *c_sandbox_engine__update__original = nullptr;

static void __fastcall game_engine_sandbox_start_editing_object(long player_index, long map_variant_index);
static decltype(game_engine_sandbox_start_editing_object) *game_engine_sandbox_start_editing_object__original = nullptr;

/* ---------- public code */

void game_engine_sandbox_hooks_initialize()
{
	c_sandbox_engine__initialize_for_new_map__original = main_get_module_offset<decltype(c_sandbox_engine__initialize_for_new_map__original)>(0x2BCA10);
	c_sandbox_engine__update__original = main_get_module_offset<decltype(c_sandbox_engine__update__original)>(0x2BD020);
	game_engine_sandbox_start_editing_object__original = main_get_module_offset<decltype(game_engine_sandbox_start_editing_object__original)>(0x2C04D0);

	DetourAttach((PVOID *)&c_sandbox_engine__update__original, c_sandbox_engine__update);
	DetourAttach((PVOID *)&c_sandbox_engine__initialize_for_new_map__original, c_sandbox_engine__initialize_for_new_map);
	DetourAttach((PVOID *)&game_engine_sandbox_start_editing_object__original, game_engine_sandbox_start_editing_object);
}

void game_engine_sandbox_hooks_dispose()
{
	DetourAttach((PVOID *)&game_engine_sandbox_start_editing_object__original, game_engine_sandbox_start_editing_object);
	DetourDetach((PVOID *)&c_sandbox_engine__initialize_for_new_map__original, c_sandbox_engine__initialize_for_new_map);
	DetourDetach((PVOID *)&c_sandbox_engine__update__original, c_sandbox_engine__update);
}

/* ---------- private code */

const wchar_t *c_simulation_history_map_variant_action::get_description() const
{
	return m_description;
}

void c_simulation_history_map_variant_action::apply()
{
	if (!game_is_authoritative() || !g_history_manager.is_recording())
	{
		return;
	}


}

c_simulation_history_map_variant_action::c_simulation_history_map_variant_action(const wchar_t *description, void *address) :
	m_description(description),
	m_map_variant_data()
{
	assert(address);
	memcpy_s(m_map_variant_data, sizeof(m_map_variant_data), address, k_map_variant_data_size);
}

static bool __fastcall c_sandbox_engine__initialize_for_new_map(void *engine, void *address)
{
	if (!c_sandbox_engine__initialize_for_new_map__original(engine, address))
	{
		return false;
	}

	g_history_manager.clear();
	g_history_manager.start_recording();

	return true;
}

static void __fastcall c_sandbox_engine__update(void *engine, void *address)
{
	c_sandbox_engine__update__original(engine, address);

	static void (*undo)() = []()
	{
		if (!g_history_manager.can_undo())
		{
			chud_messaging_post(0, L"Nothing to undo!", 0);
			return;
		}

		g_history_manager.request_undo();
	};

	static void (*redo)() = []()
	{
		if (!g_history_manager.can_redo())
		{
			chud_messaging_post(0, L"Nothing to redo!", 0);
			return;
		}

		g_history_manager.request_redo();
	};

	byte control_key_frames = input_key_frames_down(_key_control);
	byte shift_key_frames = input_key_frames_down(_key_shift);
	byte z_key_frames = input_key_frames_down(_key_z);
	byte y_key_frames = input_key_frames_down(_key_y);

	if (control_key_frames)
	{
		if (shift_key_frames && z_key_frames && (control_key_frames == 1 || shift_key_frames == 1 || z_key_frames == 1))
		{
			redo();
		}
		else if (z_key_frames && (control_key_frames == 1 || z_key_frames == 1))
		{
			undo();
		}
		else if (y_key_frames && (control_key_frames == 1 || y_key_frames == 1))
		{
			redo();
		}
	}
}

void __fastcall game_engine_sandbox_start_editing_object(long player_index, long map_variant_index)
{
	auto edit_object_action = c_simulation_history_map_variant_action(L"object grabbed", nullptr);
	game_engine_sandbox_start_editing_object__original(player_index, map_variant_index);
}
