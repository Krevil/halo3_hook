#pragma once

#include <assert.h>
#include <string.h>
#include <wchar.h>

/* ---------- macros */

#define FLAG(bit) (1ULL << (qword)(bit))
#define TEST_BIT(flags, bit) ((flags) & FLAG(bit))
#define SET_FLAG(flags, bit, value) ((flags) = ((value) ? ((flags) | FLAG(bit)) : ((flags) & ~FLAG(bit))))

#define IN_RANGE_INCLUSIVE(value, min, max) (((value) >= (min)) && ((value) <= (max)))
#define MAX_INDEX_WITH_BITS(bits) ((1U << (bits)) - 1)
#define VALID_INDEX(index, max_count) (((index) >= 0) && ((index) < (max_count)))

#define BIT_VECTOR_SIZE_IN_LONGS(bit_count) (((bit_count) + 31) >> 5)
#define BIT_VECTOR_SIZE_IN_BYTES(bit_count) (BIT_VECTOR_SIZE_IN_LONGS(bit_count) * sizeof(long))
#define BIT_VECTOR_WORD_INDEX(bit) ((bit) >> 5)
#define BIT_VECTOR_WORD(vector, bit) ((vector)[BIT_VECTOR_WORD_INDEX(bit)])
#define BIT_VECTOR_TEST_FLAG(vector, bit) TEST_BIT(BIT_VECTOR_WORD(vector, bit), (bit) % (sizeof(long) * 8))
#define BIT_VECTOR_SET_FLAG(vector, bit, value) SET_FLAG(BIT_VECTOR_WORD(vector, bit), ((bit) % (sizeof(long) * 8)), value)

/* ---------- types */

enum e_none_sentinel
{
    NONE = -1
};

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef unsigned long long qword;

typedef unsigned short half;
typedef float real;

typedef unsigned long tag;

/* ---------- constants */

enum : long long
{
    INT64_BITS = 64,
    INT64_BITS_BITS = 6,

    UNSIGNED_LONG_MAX = 4294967295,
    LONG_MAX = 2147483647,
    LONG_MIN = -2147483648,
    LONG_BITS = 32,
    LONG_BITS_BITS = 5,
    LONG_MASK = ((1ULL << LONG_BITS) - 1),

    UNSIGNED_SHORT_MAX = 65535,
    SHORT_BITS = 16,
    SHORT_BITS_BITS = 4,
    SHORT_MASK = ((1U << SHORT_BITS) - 1),

    UNSIGNED_CHAR_MAX = 255,
    CHAR_MAX = 127,
    CHAR_MIN = -128,
    CHAR_BITS = 8,
    CHAR_BITS_BITS = 3,
    CHAR_MASK = ((1U << CHAR_BITS) - 1),

    BYTE_BITS = 8,
    BYTE_BITS_BITS = 3,

    WCHAR_BITS = 16,
};

enum // indices per point or vector
{
    _x,
    _y,
    _z,
    _w,
    _i = _x,
    _j = _y,
    _k = _z,
};

enum // vertices per rectangle
{
    _rectangle_top_left,
    _rectangle_bottom_left,
    _rectangle_top_right,
    _rectangle_bottom_right,
    k_vertices_per_rectangle_count
};

enum // vertices per pyramid
{
    _pyramid_top_left,
    _pyramid_bottom_left,
    _pyramid_top_right,
    _pyramid_bottom_right,
    _pyramid_tip,
    k_vertices_per_pyramid_count
};

enum // planes per frustum
{
    _frustum_plane_left,
    _frustum_plane_right,
    _frustum_plane_top,
    _frustum_plane_bottom,
    _frustum_plane_near,
    _frustum_plane_far,
    k_planes_per_frustum_count
};

/* ---------- types traits */

template <typename t_lhs_type, typename t_rhs_type>
constexpr bool is_convertible_to = __is_convertible_to(t_lhs_type, t_rhs_type);

template <typename t_type>
constexpr bool is_enum = __is_enum(t_type);

template <typename, typename>
constexpr bool is_same = false;

template <typename t_type>
constexpr bool is_same<t_type, t_type> = true;

template <typename, typename...>
constexpr bool is_any = false;

template <typename t_type1, typename t_type2, typename... t_types>
constexpr bool is_any<t_type1, t_type2, t_types...> =
is_same<t_type1, t_type2> ||
is_any<t_type1, t_types...>;

template <typename t_base, typename t_derived>
constexpr bool is_base_of = __is_base_of(t_base, t_derived);

template <template <typename...> typename t_template_type, typename t_type>
constexpr bool is_template_of = false;

template <template <typename...> typename t_template_type, typename... t_types>
constexpr bool is_template_of<t_template_type, t_template_type<t_types...>> = true;

template <template <typename, const long> typename t_template_type, typename t_type>
constexpr bool is_ranged_template_of = false;

template <template <typename, const long> typename t_template_type, typename t_type, const long k_value>
constexpr bool is_ranged_template_of<t_template_type, t_template_type<t_type, k_value>> = true;

/* ---------- bsp types */

struct s_portal_reference
{
    short bsp_index : 6;
    short portal_index : 10;
};

struct s_cluster_reference
{
    char bsp_index;
    char cluster_index;
};

struct s_location
{
    s_cluster_reference cluster_reference;
    word leaf_index;
};

/* ---------- math types */

union byte_rectangle3d
{
    struct
    {
        char x0, x1;
        char y0, y1;
        char z0, z1;
    };
    char n[6];
};

union point2d
{
    struct { short x, y; };
    short n[2];
};

union long_point2d
{
    struct { long x, y; };
    long n[2];
};

union point3d
{
    struct
    {
        short x, y, z;
    };
    short n[3];
};

union long_point3d
{
    struct { long x, y, z; };
    long n[3];
};

union point4d
{
    struct { short x, y, z, w; };
    short n[4];
};

union long_point4d
{
    struct { long x, y, z, w; };
    long n[4];
};

union rectangle2d
{
    struct { short y0, x0, y1, x1; };
    short m[2][2];
    short n[4];
};

union long_rectangle2d
{
    struct { long y0, x0, y1, x1; };
    long m[2][2];
    long n[4];
};

union long_rectangle3d
{
    struct { long x0, x1, y0, y1, z0, z1; };
    long n[6];
};

union rgb_color
{
    struct { word red, green, blue; };
    word n[3];
};

union argb_color
{
    struct
    {
        word alpha;
        rgb_color rgb;
    };
    struct
    {
        byte gap0[2];
        word red;
        word green;
        word blue;
    };
    word n[4];
};

union hsv_color
{
    struct
    {
        word hue;
        word saturation;
        word value;
    };
    word n[3];
};

union ahsv_color
{
    struct
    {
        word alpha;
        hsv_color hsv;
    };
    struct
    {
        byte gap0[2];
        word hue;
        word saturation;
        word value;
    };
    word n[4];
};

union real_rgb_color
{
    struct { real red, green, blue; };
    real n[3];
};

union half_rgb_color
{
    struct
    {
        half red;
        half green;
        half blue;
    };
    half n[3];
};

union real_argb_color
{
    struct { real alpha, red, green, blue; };
    real n[4];
};

union real_abgr_color
{
    struct { real alpha, blue, green, red; };
    real n[4];
};

union half_argb_color
{
    struct
    {
        half alpha;
        half red;
        half green;
        half blue;
    };
    half n[4];
};

union half_abgr_color
{
    struct
    {
        half alpha;
        half blue;
        half green;
        half red;
    };
    half n[4];
};

union real_hsv_color
{
    struct { real hue, saturation, value; };
    real n[3];
};

union real_ahsv_color
{
    struct
    {
        real alpha;
        real_hsv_color hsv;
    };
    struct
    {
        byte gap0[sizeof(real)];
        real hue;
        real saturation;
        real value;
    };
    real n[4];
};

union real_point2d
{
    struct { real x, y; };
    struct { real u, v; };
    real n[2];
};

union real_point3d
{
    struct { real x, y, z; };
    struct { real u, v, w; };
    real n[3];
};

union real_vector2d
{
    struct { real i, j; };
    real n[2];
};

union real_bounds2d
{
    struct { real min, max; };
    real n[2];
};

union real_vector3d
{
    struct { real i, j, k; };
    real n[3];
};

union half_vector3d
{
    struct { half i, j, k; };
    half n[3];
};

union real_vector4d
{
    struct { real i, j, k, l; };
    real n[4];
};

struct real_plane2d
{
    real_vector2d n;
    real d;
};

struct real_plane3d
{
    real_vector3d n;
    real d;
};

union real_rectangle2d
{
    struct { real x0, x1, y0, y1; };
    real m[2][2];
    real n[4];
};

union real_rectangle3d
{
    struct { real x0, x1, y0, y1, z0, z1; };
    real m[3][2];
    real n[6];
};

struct real_quaternion
{
    real_vector3d v;
    real w;
};

struct real_orientation
{
    real_quaternion rotation;
    real_point3d translation;
    real scale;
};

union real_euler_angles2d
{
    union { real yaw, pitch; };
    real n[2];
};

union real_euler_angles3d
{
    union { real yaw, pitch, roll; };
    real n[3];
};

struct real_matrix3x3
{
    union
    {
        struct
        {
            real_vector3d forward;
            real_vector3d left;
            real_vector3d up;
        };
        real_vector3d basis[3];
        real n[3][3];
    };
};

struct real_matrix4x3
{
    real scale;
    union
    {
        struct
        {
            real_vector3d forward;
            real_vector3d left;
            real_vector3d up;
        };
        struct
        {
            real_vector3d basis[3];
            real_point3d position;
        };
        struct
        {
            real_matrix3x3 matrix3x3;
            real_point3d origin;
        };
        real n[4][3];
    };
};

union double_point3d
{
    struct { long double x, y, z; };
    struct { long double u, v, w; };
    long double n[3];
};

union double_vector3d
{
    struct { long double i, j, k; };
    long double n[3];
};

struct double_plane3d
{
    double_vector3d n;
    long double d;
};

/* ---------- memory management */

template <typename t_type>
struct ptr32_t
{
    dword m_stored;
};
