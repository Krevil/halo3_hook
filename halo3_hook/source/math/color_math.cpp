
#include <main/main.h>
#include <math/color_math.h>

/* ---------- code */

void __fastcall set_real_linear_rgb_color(
	real_linear_rgb_color *result,
	real red,
	real green,
	real blue)
{
	main_get_typed_module_address<decltype(&set_real_linear_rgb_color)>(0x377030)(result, red, green, blue);
}
