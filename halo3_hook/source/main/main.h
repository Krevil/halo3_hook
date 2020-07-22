#pragma once

#include <cseries/cseries.h>

/* ---------- prototypes/main.cpp */

bool main_initialize(void *base_address);
void main_dispose();

bool main_initialized();
void *main_get_base_address();
void *main_get_module_address(qword offset = 0);
void *main_get_tls_address(qword offset = 0);

/* ---------- inline code */

template <typename t_type>
inline t_type main_get_typed_module_address(qword offset = 0)
{
	return (t_type)main_get_module_address(offset);
}

template <typename t_type>
inline t_type main_get_typed_tls_address(qword offset = 0)
{
	return (t_type)main_get_tls_address(offset);
}
