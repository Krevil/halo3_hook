/*
static_arrays.h
    Static array declarations and templates.
*/

#pragma once

#include <cseries/cseries.h>

template <typename t_element, const long k_maximum_count>
requires (k_maximum_count > 0)
class c_static_array final
{
private:
    t_element m_elements[k_maximum_count];

public:
    inline static long get_count()
    {
        return k_maximum_count;
    }

    inline static bool valid(long index)
    {
        return index <= get_count();
    }

    t_element *begin()
    {
        return m_elements;
    }

    t_element *end()
    {
        return m_elements + k_maximum_count;
    }

    const t_element *begin() const
    {
        return m_elements;
    }

    const t_element *end() const
    {
        return m_elements + k_maximum_count;
    }

    void set_all(const t_element &value)
    {
        for (t_element &i : *this)
        {
            i = value;
        }
    }

    t_element &operator[](long index)
    {
        assert(valid(index));
        return m_elements[index];
    }

    const t_element &operator[](long index) const
    {
        assert(valid(index));
        return m_elements[index];
    }

    operator t_element *()
    {
        return m_elements;
    }

    operator const t_element *() const
    {
        return m_elements;
    }
};

template <typename t_element, const long k_maximum_count>
requires (k_maximum_count > 0)
class c_static_stack
{
private:
    long m_count;
    t_element m_elements[k_maximum_count];

public:
    c_static_stack() :
        m_count(0),
        m_elements()
    {
    }

    void clear()
    {
        m_count = 0;
        memset(m_elements, 0, sizeof(m_elements));
    }

    bool valid() const
    {
        return m_count <= k_maximum_count;
    }

    bool valid(long index) const
    {
        return VALID_INDEX(index, k_maximum_count);
    }

    bool empty() const
    {
        return m_count == 0;
    }

    bool full() const
    {
        return m_count == k_maximum_count;
    }

    long count() const
    {
        return m_count;
    }

    static long maximum_count()
    {
        return k_maximum_count;
    }

    t_element &get(long index)
    {
        assert(valid(index));
        return m_elements[index];
    }

    t_element *get_elements()
    {
        return m_elements;
    }

    void resize(long size)
    {
        m_count = size;
        assert(valid());
    }

    long push()
    {
        assert(!full());
        return m_count++;
    }

    void push_top(const t_element &value)
    {
        get(push()) = value;
    }

    void push_bottom(const t_element &value)
    {
        if (!empty())
        {
            for (long i = 1; i < m_count; i++)
            {
                m_elements[i] = m_elements[i - 1];
            }
        }

        m_elements[0] = value;
    }

    void pop_top()
    {
        assert(!empty());
        m_count--;
    }

    void pop_bottom()
    {
        assert(!empty());
        
        for (long i = 1; i < m_count; i++)
        {
            m_elements[i - 1] = m_elements[i];
        }

        m_count--;
    }

    long top() const
    {
        assert(!empty());
        return m_count - 1;
    }

    t_element &get_top()
    {
        return get(top());
    }

    t_element &get_bottom()
    {
        assert(!empty());
        return get(0);
    }

    t_element *begin()
    {
        return m_elements;
    }

    t_element *end()
    {
        return m_elements + m_count;
    }

    t_element &operator[](long index)
    {
        assert(valid(index));
        return m_elements[index];
    }
};

template <typename t_element, const long k_maximum_count, const long k_value>
requires (k_maximum_count > 0)
class c_static_aligned_stack_allocator
{
private:
    long m_count;
    long m_pad0;
    long m_pad1;
    long m_pad2;
    t_element m_elements[k_maximum_count];

public:
    // TODO: methods
};

template <const long k_bit_count>
requires (k_bit_count > 0)
class c_static_flags_no_init
{
    enum
    {
        k_size_in_dwords = BIT_VECTOR_SIZE_IN_LONGS(k_bit_count)
    };

protected:
    dword m_flags[k_size_in_dwords];

public:
    // TODO: methods
};

template <const long k_bit_count>
requires (k_bit_count > 0)
class c_static_flags :
    public c_static_flags_no_init<k_bit_count>
{
protected:
    using c_static_flags_no_init<k_bit_count>::m_flags;

public:
    // TODO: methods
};

template <const long k_element_count>
requires (k_element_count > 0)
class c_static_string final
{
private:
    char m_string[k_element_count];

public:
    static const long element_count = k_element_count;

    char *begin()
    {
        return m_string;
    }

    char *end()
    {
        return m_string + k_element_count;
    }

    const char *begin() const
    {
        return m_string;
    }

    const char *end() const
    {
        return m_string + k_element_count;
    }

    char &operator[](long index)
    {
        return m_string[index];
    }

    char operator[](long index) const
    {
        return m_string[index];
    }
};

class c_string_builder
{
public:
    // TODO: methods
};

template <const long k_maximum_length>
requires (k_maximum_length > 0)
class c_static_wchar_string
{
private:
    wchar_t m_string[256];

public:
    // TODO: methods
};

template <
    typename t_enum,
    typename t_storage,
    const long k_number_of_bits = sizeof(t_storage) * 8>
requires
    is_enum<t_enum> &&
    (k_number_of_bits <= sizeof(t_storage) * 8)
class c_flags_no_init
{
protected:
    t_storage m_stored;

public:
    void clear()
    {
        m_stored = 0;
    }

    bool test(t_enum bit) const
    {
        return (m_stored & static_cast<t_storage>(FLAG(bit))) != 0;
    }

    void set(t_enum bit, bool value)
    {
        t_storage flag = static_cast<t_storage>(FLAG(bit));

        if (value)
            m_stored |= flag;
        else
            m_stored &= ~flag;
    }

    bool valid() const
    {
        auto total_bits = sizeof(t_storage) * 8;

        for (auto current_bit = k_number_of_bits;
            current_bit < total_bits;
            current_bit++)
        {
            if (TEST_BIT(m_stored, current_bit))
                return false;
        }

        return true;
    }

    t_storage get_unsafe() const
    {
        return m_stored;
    }
};

template <
    typename t_enum,
    typename t_storage,
    const long k_number_of_bits = sizeof(t_storage) * 8>
class c_flags :
    public c_flags_no_init<t_enum, t_storage, k_number_of_bits>
{
protected:
    using c_flags_no_init<t_enum, t_storage, k_number_of_bits>::m_stored;

public:
    c_flags()
    {
        m_stored = (t_storage)0;
    }

    c_flags(const t_storage &value)
    {
        m_stored = value;
    }
};

template <
    typename t_enum,
    typename t_storage,
    const t_storage k_first_option,
    const t_storage k_option_count>
requires
    (is_enum<t_enum> || is_convertible_to<t_enum, long>) &&
    is_convertible_to<t_storage, long>
class c_enum_no_init
{
private:
    t_storage m_storage;

public:
    // TODO: methods
};

template <
    typename t_enum,
    typename t_storage,
    const t_storage k_first_option,
    const t_storage k_option_count>
requires
    (is_enum<t_enum> || is_convertible_to<t_enum, long>) &&
    is_convertible_to<t_storage, long>
class c_enum :
    public c_enum_no_init<t_enum, t_storage, k_first_option, k_option_count>
{
public:
    // TODO: methods
};

template <const long k_alignment>
requires (k_alignment > 0)
struct __declspec(align(k_alignment)) s_aligned_type_for_union_alignment
{
    char _;
};

template <typename t_type, const long k_size, const long k_alignment>
requires (k_size > 0) && (k_alignment > 0)
class c_opaque_data
{
private:
    union
    {
        s_aligned_type_for_union_alignment<k_alignment> m_force_alignment;
        char m_opaque_data[k_size];
    };

public:
    // TODO: methods
};
