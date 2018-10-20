//
// Created by fr0streaper on 20/10/18.
//

#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include <memory>

template <typename T>
struct optional
{

    optional();

    optional(T const&);

    optional(optional<T> const&);

    optional<T>& operator=(optional<T> const&);

    explicit operator bool() const;

    T& operator*();
    T const& operator*() const;

    T* operator->();
    T const* operator->() const;

    void clear();

    template <typename U>
    friend void swap(optional<U>&, optional<U>&);

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

    bool is_empty;
    std::unique_ptr<T> value;

};


#endif //OPTIONAL_OPTIONAL_H
