//
// Created by fr0streaper on 20/10/18.
//

#include <type_traits>
#include <utility>

#include "tests.inl"
#include "optional.h"

template <typename T>
optional<T>::optional() : is_empty(true) {}

template <typename T>
optional<T>::optional(T const& _value) : is_empty(false)
{
    value = std::unique_ptr<T>(new T(_value));
}

template <typename T>
optional<T>::optional(optional<T> const& rhs)
{
    is_empty = rhs.is_empty;
    if (!is_empty)
    {
        value = std::unique_ptr<T>(new T(*rhs.value));
    }
}

template <typename T>
optional<T>& optional<T>::operator=(optional<T> const& rhs)
{
    is_empty = rhs.is_empty;
    if (!is_empty)
    {
        value = std::unique_ptr<T>(new T(*rhs.value));
    }

    return *this;
}

template <typename T>
optional<T>::operator bool() const
{
    return !is_empty;
}

template <typename T>
T& optional<T>::operator*()
{
    if (is_empty)
    {
        throw std::runtime_error("Dereference attempted on empty object");
    }
    return (*value);
}
template <typename T>
T const& optional<T>::operator*() const
{
    if (is_empty)
    {
        throw std::runtime_error("Dereference attempted on empty object");
    }
    return (*value);
}

template <typename T>
T* optional<T>::operator->()
{
    if (is_empty)
    {
        return nullptr;
    }
    return value.get();
}
template <typename T>
T const* optional<T>::operator->() const
{
    if (is_empty)
    {
        return nullptr;
    }
    return value.get();
}

template <typename T>
void optional<T>::clear()
{
    is_empty = true;
}

template <typename T>
void swap(optional<T>& a, optional<T>& b)
{
    if (a && b)
    {
        swap(a.value, b.value);
    }
    else if (a)
    {
        b = a;
        a.clear();
    }
    else if (b)
    {
        a = b;
        b.clear();
    }
}

template <typename T>
decltype((std::declval<T>() < std::declval<T>()), bool())
operator<(optional<T> const& a, optional<T> const& b)
{
    if (!b)
    {
        return false;
    }
    if (!a)
    {
        return true;
    }

    return *a.value < *b.value;
}

template <typename T>
decltype((std::declval<T>() <= std::declval<T>()), bool())
operator<=(optional<T> const& a, optional<T> const& b)
{
    if (!a)
    {
        return true;
    }
    if (!b)
    {
        return false;
    }

    return *a.value <= *b.value;
}

template <typename T>
decltype((std::declval<T>() == std::declval<T>()), bool())
operator==(optional<T> const& a, optional<T> const& b)
{
    if (static_cast<bool>(a) != static_cast<bool>(b))
    {
        return false;
    }
    if (!a)
    {
        return true;
    }
    return *a.value == *b.value;
}

template <typename T>
decltype((std::declval<T>() == std::declval<T>()), bool())
operator!=(optional<T> const& a, optional<T> const& b)
{
    return !(a == b);
}

template <typename T>
decltype((std::declval<T>() >= std::declval<T>()), bool())
operator>=(optional<T> const& a, optional<T> const& b)
{
    if (!b)
    {
        return true;
    }
    if (!a)
    {
        return false;
    }

    return *a.value >= *b.value;
}

template <typename T>
decltype((std::declval<T>() > std::declval<T>()), bool())
operator>(optional<T> const& a, optional<T> const& b)
{
    if (!a)
    {
        return false;
    }
    if (!b)
    {
        return true;
    }

    return *a.value > *b.value;
}