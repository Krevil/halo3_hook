#include <interface/mainmenu/mainmenu.h>
#include <main/main.h>


/* Requires a mainmenu.map to be present */

void mainmenu_set_enabled(bool enabled)
{
	byte *mainmenu_jg = main_get_typed_module_address<byte *>(0x2d2890);
	byte *mainmenu_jne = main_get_typed_module_address<byte *>(0x2d73a1);
	byte *mainmenu_cmp = main_get_typed_module_address<byte *>(0x2d739e);
	byte *mainmenu_je_6 = main_get_typed_module_address<byte *>(0x2d74e3);
	byte *mainmenu_je_2 = main_get_typed_module_address<byte *>(0x13641e);
	byte *game_engine_mode = *main_get_typed_module_address<byte **>(0x1cb15c8);
	if (enabled)
	{
		mainmenu_jg[0] = 0x90, mainmenu_jg[1] = 0x90;
		mainmenu_jne[1] = 0x85;
		mainmenu_cmp[0] = 0x90, mainmenu_cmp[1] = 0x90, mainmenu_cmp[2] = 0x90;
		mainmenu_je_6[0] = 0x90, mainmenu_je_6[1] = 0x90, mainmenu_je_6[2] = 0x90, mainmenu_je_6[3] = 0x90, mainmenu_je_6[4] = 0x90, mainmenu_je_6[5] = 0x90;
		mainmenu_je_2[0] = 0x90, mainmenu_je_2[1] = 0x90;
		game_engine_mode[0x26C] = 3;
	}
	else
	{
		mainmenu_jg[0] = 0x7F, mainmenu_jg[1] = 0x08;
		mainmenu_jne[1] = 0x84;
		mainmenu_cmp[0] = 0x4D, mainmenu_cmp[1] = 0x85, mainmenu_cmp[2] = 0xC9;
		mainmenu_je_6[0] = 0x0F, mainmenu_je_6[1] = 0x84, mainmenu_je_6[2] = 0x9F, mainmenu_je_6[3] = 0x00, mainmenu_je_6[4] = 0x00, mainmenu_je_6[5] = 0x00;
		mainmenu_je_2[0] = 0x74, mainmenu_je_2[1] = 0x7E;
		game_engine_mode[0x26C] = 0;
	}
}