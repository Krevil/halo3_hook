
#include <interface/chud/chud_messaging.h>
#include <main/main.h>

/* ---------- public code */

void __fastcall chud_messaging_post(long long user_index, const wchar_t *buffer, long context)
{
	main_get_typed_module_address<decltype(&chud_messaging_post)>(0x2E0C08)((*main_get_typed_tls_address<long long*>((user_index * 0x28e0) + 0x108) + 0x2000), buffer, context);
}
