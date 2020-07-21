#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/render_objects.cpp */

void render_object_hooks_initialize();
void render_object_hooks_dispose();

bool render_objects_motion_blur_enabled();
void render_objects_set_motion_blur_enabled(bool enabled);
