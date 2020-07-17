#pragma once

/* ---------- globals */

extern void *(__fastcall *object_try_and_get_multiplayer)(long object_index);

/* ---------- prototypes/object_hooks.cpp */

void object_hooks_initialize();
void object_hooks_dispose();
