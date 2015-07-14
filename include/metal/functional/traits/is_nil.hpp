// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef METAL_FUNCTIONAL_TRAITS_IS_NIL_HPP
#define METAL_FUNCTIONAL_TRAITS_IS_NIL_HPP

#include <metal/algebra/logical/not.hpp>
#include <metal/algebra/logical/and.hpp>
#include <metal/detail/introspection.hpp>

#include <type_traits>

namespace metal
{
    namespace detail
    {
        METAL_DEFINE_NESTED_TYPE_TRAIT(has_type, type);
    }

    /// \ingroup functional_traits
    /// \brief Checks whether a \nullable is empty.
    ///
    /// Usage
    /// -----
    /// For any \nullable `n`,
    /// \code
    ///     using result = metal::is_nil<n>;
    /// \endcode
    ///
    /// \par Return Type:
    ///     \numerical
    ///
    /// \par Semantics:
    ///     if `n::type` is undefined or ambiguously defined, then equivalent to
    ///     \code
    ///         struct result :
    ///             std::true_type
    ///         {};
    ///     \endcode
    ///     otherwise, equivalent to
    ///     \code
    ///         struct result :
    ///             std::false_type
    ///         {};
    ///     \endcode
    ///
    /// Example
    /// -------
    /// \snippet functional/traits/is_nil.cpp main
    ///
    /// See Also
    /// --------
    /// \see is_strict
    template<typename n>
    struct is_nil :
            not_<and_<std::is_class<n>, detail::has_type<n>>>
    {};

    /// \ingroup functional_traits
    /// \brief Eager adaptor for \ref is_nil.
    template<typename n>
    using is_nil_t = typename is_nil<n>::type;
}

#endif
