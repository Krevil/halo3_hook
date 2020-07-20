#pragma once

#include <cseries/cseries.h>

/* ---------- constants */

enum e_rgb_colors_interpolate_flags
{
    _rgb_colors_interpolate_in_hsv_space_bit,
    _rgb_colors_interpolate_along_farthest_hue_path_bit,
    k_number_of_rgb_colors_interpolate_flags
};

/* ---------- structures */

struct real_linear_rgb_color
{
    real red;
    real green;
    real blue;
};

struct real_rgb_radiance
{
    real red;
    real green;
    real blue;
};

struct real_xyz_radiance
{
    real x;
    real y;
    real z;
};

struct real_linear_xyz_color
{
    real x;
    real y;
    real z;
};

struct real_rgb_lightprobe
{
    real red_terms[9];
    real green_terms[9];
    real blue_terms[9];
};

struct real_rgb_mini_lightprobe
{
    real red_terms[4];
    real green_terms[4];
    real blue_terms[4];
};

struct half_linear_rgb_color
{
    half red;
    half green;
    half blue;
    half pad;
};

struct half_rgb_lightprobe
{
    half red_terms[9];
    half green_terms[9];
    half blue_terms[9];
    half pad;
};

struct half_rgb_mini_lightprobe
{
    half red_terms[4];
    half green_terms[4];
    half blue_terms[4];
};

struct half_rgb_lightprobe_with_dominant_light
{
    half_vector3d dominant_light_direction;
    half pad;
    half_linear_rgb_color dominant_light_intensity;
    half_rgb_lightprobe quadratic_probe;
};

struct real_ycbcr_color
{
    real y;
    real cb;
    real cr;
};

struct real_ycbcr_lightprobe
{
    real_ycbcr_color terms[9];
};

struct s_faux_logluv_lightprobe
{
    dword terms[9];
};

/* ---------- prototypes/color_math.cpp */

void __fastcall set_real_linear_rgb_color(real_linear_rgb_color *result, real red, real green, real blue);
