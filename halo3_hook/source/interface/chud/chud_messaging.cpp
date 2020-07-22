
#include <interface/chud/chud_messaging.h>
#include <main/main.h>

/* ---------- public code */

void __fastcall chud_messaging_post(long user_index, const wchar_t *buffer, long context)
{
	main_get_typed_module_address<decltype(&chud_messaging_post)>(0x4CE490)(user_index, buffer, context);
}
