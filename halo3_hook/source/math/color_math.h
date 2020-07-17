#pragma once

/* ---------- structures */

struct real_linear_rgb_color
{
	float red;
	float green;
	float blue;
};

/* ---------- prototypes/color_math.cpp */

void __fastcall set_real_linear_rgb_color(real_linear_rgb_color *result, float red, float green, float blue);
