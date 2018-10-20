//
// Created by fr0streaper on 20/10/18.
//

#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include <utility>
#include <memory>

template <typename T>
struct optional {

    optional() {}

    optional(T const &_value)
    {
        value = std::unique_ptr<T>(new T(_value));
    }

    optional(optional<T> const &rhs)
    {
        if (rhs)
        {
            value = std::unique_ptr<T>(new T(*rhs.value));
        }
        else if (value)
        {
            value.reset();
        }
    }

    optional<T> &operator=(optional<T> const &rhs)
    {
        if (rhs)
        {
            value = std::unique_ptr<T>(new T(*rhs.value));
        }
        else if (value)
        {
            value.reset();
        }

        return *this;
    }

    explicit operator bool() const
    {
        return static_cast<bool>(value);
    }

    T &operator*()
    {
        if (!value)
        {
            throw std::runtime_error("Runtime error: dereference of empty optional object");
        }
        return (*value);
    }
    T const& operator*() const
    {
        if (!value)
        {
            throw std::runtime_error("Runtime error: dereference of empty optional object");
        }
        return (*value);
    }

    T* operator->()
    {
        if (!value)
        {
            throw std::runtime_error("Runtime error: dereference of empty optional object");
        }
        return value.get();
    }
    T const* operator->() const
    {
        if (!value)
        {
            throw std::runtime_error("Runtime error: dereference of empty optional object");
        }
        return value.get();
    }

    void clear()
    {
        value.reset();
    }

    template <typename U>
    friend void swap(optional<U>& a, optional<U>& b);

    template <typename U>
    friend decltype((std::declval<U>() < std::declval<U>()), bool())
    operator<(optional<U> const&, optional<U> const&);

    template <typename U>
    friend decltype((std::declval<U>() <= std::declval<U>()), bool())
    operator<=(optional<U> const&, optional<U> const&);

    template <typename U>
    friend decltype((std::declval<U>() == std::declval<U>()), bool())
    operator==(optional<U> const&, optional<U> const&);

    template <typename U>
    friend decltype((std::declval<U>() == std::declval<U>()), bool())
    operator!=(optional<U> const&, optional<U> const&);

    template <typename U>
    friend decltype((std::declval<U>() >= std::declval<U>()), bool())
    operator>=(optional<U> const&, optional<U> const&);

    template <typename U>
    friend decltype((std::declval<U>() > std::declval<U>()), bool())
    operator>(optional<U> const&, optional<U> const&);

private:

    std::unique_ptr<T> value;

};

template <typename U>
void swap(optional<U>& a, optional<U>& b)
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

template <typename U>
decltype((std::declval<U>() < std::declval<U>()), bool())
operator<(optional<U> const& a, optional<U> const& b)
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

template <typename U>
decltype((std::declval<U>() <= std::declval<U>()), bool())
operator<=(optional<U> const& a, optional<U> const& b)
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

template <typename U>
decltype((std::declval<U>() == std::declval<U>()), bool())
operator==(optional<U> const& a, optional<U> const& b)
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

template <typename U>
decltype((std::declval<U>() == std::declval<U>()), bool())
operator!=(optional<U> const& a, optional<U> const& b)
{
    return !(a == b);
}

template <typename U>
decltype((std::declval<U>() >= std::declval<U>()), bool())
operator>=(optional<U> const& a, optional<U> const& b)
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

template <typename U>
decltype((std::declval<U>() > std::declval<U>()), bool())
operator>(optional<U> const& a, optional<U> const& b)
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


#endif //OPTIONAL_OPTIONAL_H
