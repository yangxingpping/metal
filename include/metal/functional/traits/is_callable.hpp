// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef METAL_FUNCTIONAL_TRAITS_IS_CALLABLE_HPP
#define METAL_FUNCTIONAL_TRAITS_IS_CALLABLE_HPP

#include <metal/functional/call.hpp>
#include <metal/functional/traits/is_evaluable.hpp>

namespace metal
{
    template<typename... values>
    struct is_callable :
            is_evaluable<call, values...>
    {};

    /// \ingroup functional_traits
    /// \brief Eager adaptor for \ref is_callable.
    template<typename... values>
    using is_callable_t = typename is_callable<values...>::type;
}

#endif
