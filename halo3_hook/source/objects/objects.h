#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/object_hooks.cpp */

void object_hooks_initialize();
void object_hooks_dispose();

void *object_try_and_get_and_verify_type(long object_index, dword valid_type_flags);
