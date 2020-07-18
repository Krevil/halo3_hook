#pragma once

/* ---------- prototypes/light_hooks.cpp */

void light_hooks_initialize();
void light_hooks_dispose();

void lights_set_forced_color(bool enabled, float red = 0.0f, float green = 0.0f, float blue = 0.0f);
