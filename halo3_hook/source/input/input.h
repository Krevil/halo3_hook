#pragma once

#include <cseries/cseries.h>
#include <input/input_constants.h>

/* ---------- prototypes/input.cpp */

void input_hooks_initialize();
void input_hooks_dispose();

byte __fastcall input_key_frames_down(short key_code);
byte __fastcall input_mouse_button_frames_down(short button_index);

bool input_update();
