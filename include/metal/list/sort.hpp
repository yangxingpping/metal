// Copyright Bruno Dutra 2015-2017
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#ifndef METAL_LIST_SORT_HPP
#define METAL_LIST_SORT_HPP

#include "../config.hpp"
#include "../detail/sfinae.hpp"

namespace metal {
    /// \cond
    namespace detail {
        template<typename lbd>
        struct _sort;
    }
    /// \endcond

    /// \ingroup list
    ///
    /// ### Description
    /// Sorts the elements of a \list according to an ordering relation.
    ///
    /// \tip{The sorting is [stable] if the ordering relation is [strict].}
    /// [stable]: https://en.wikipedia.org/wiki/Sorting_algorithm#Stability
    /// [strict]: https://en.wikipedia.org/wiki/Weak_ordering#Strict_weak_orderings
    ///
    /// ### Usage
    /// For any \list `l` and \lambda `lbd`
    /// \code
    ///     using result = metal::sort<l, lbd>;
    /// \endcode
    ///
    /// \pre: For any two \values `val_i` and `val_j` contained in `l`
    /// `metal::expr<val_i, val_j>` returns a \number
    /// \returns: \list
    /// \semantics:
    ///     Equivalent to
    ///     \code
    ///         using result = metal::list<val_0, ..., val_m-1>;
    ///     \endcode
    ///     where `val_0, ..., val_m-1` is a permutation of the elements in `l`
    ///     such that `metal::expr<val_i, val_i+1>{} != false` for all
    ///     `i` in `[0, m-2]`.
    ///
    /// ### Example
    /// \snippet list.cpp sort
    ///
    /// ### See Also
    /// \see list, reverse, rotate
    template<typename seq, typename lbd>
    using sort = detail::call<detail::_sort<lbd>::template type, seq>;
}

#include "../list/list.hpp"
#include "../list/range.hpp"
#include "../lambda/lambda.hpp"
#include "../number/number.hpp"
#include "../number/if.hpp"

namespace metal {
    /// \cond
    namespace detail {
        template<typename>
        struct cons
        {};

        template<typename h, typename... t>
        struct cons<list<h, t...>>
        {
            using head = h;
            using tail = list<t...>;
        };

        template<typename seq>
        using head = typename cons<seq>::head;

        template<typename seq>
        using tail = typename cons<seq>::tail;

        template<typename x, typename y, typename... zs>
        struct _merge
        {
            template<template<typename...> class expr>
            using type = typename if_<
                expr<head<y>, head<x>>,
                _merge<x, tail<y>, zs..., head<y>>,
                _merge<tail<x>, y, zs..., head<x>>
            >::template type<expr>;
        };

        template<typename... xs, typename... zs>
        struct _merge<list<xs...>, list<>, zs...>
        {
            template<template<typename...> class>
            using type = list<zs..., xs...>;
        };

        template<typename... ys, typename... zs>
        struct _merge<list<>, list<ys...>, zs...>
        {
            template<template<typename...> class>
            using type = list<zs..., ys...>;
        };

        template<typename... zs>
        struct _merge<list<>, list<>, zs...>
        {
            template<template<typename...> class>
            using type = list<zs...>;
        };

        template<typename seq>
        struct _sort_impl
        {};

        template<typename... vals>
        struct _sort_impl<list<vals...>>
        {
            using seq = list<vals...>;
            using beg = number<0>;
            using mid = number<sizeof...(vals)/2>;
            using end = number<sizeof...(vals)>;

            using x = _sort_impl<range<seq, beg, mid>>;
            using y = _sort_impl<range<seq, mid, end>>;

            template<template<typename...> class expr>
            using type = typename _merge<
                forward<x::template type, expr>,
                forward<y::template type, expr>
            >::template type<expr>;
        };

        template<typename x, typename y>
        struct _sort_impl<list<x, y>>
        {
            template<template<typename...> class expr>
            using type = if_<expr<y, x>, list<y, x>, list<x, y>>;
        };

        template<typename x>
        struct _sort_impl<list<x>>
        {
            template<template<typename...> class>
            using type = list<x>;
        };

        template<>
        struct _sort_impl<list<>>
        {
            template<template<typename...> class>
            using type = list<>;
        };

        template<typename lbd>
        struct _sort
        {};

        template<template<typename...> class expr>
        struct _sort<lambda<expr>>
        {
            template<typename seq>
            using type = forward<_sort_impl<seq>::template type, expr>;
        };
    }
    /// \endcond
}

#endif
