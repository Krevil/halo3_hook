#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/light_hooks.cpp */

void light_hooks_initialize();
void light_hooks_dispose();

void lights_set_forced_color(bool enabled, real red = 0.0f, real green = 0.0f, real blue = 0.0f);
