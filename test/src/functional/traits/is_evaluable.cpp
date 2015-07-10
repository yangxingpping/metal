// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#include <metal/functional/traits/is_evaluable.hpp>

#include "test/atoms.hpp"
#include "test/expressions.hpp"
#include "test/main.hpp"

using namespace metal;

namespace example
{
    /// [is_evaluable]
    template<typename...>
    struct evaluable
    {
        struct type;
    };

    template<typename...>
    struct not_evaluable
    {
        //empty
    };

    static_assert(metal::is_evaluable<evaluable>::value, "");
    static_assert(metal::is_evaluable<evaluable, void>::value, "");
    static_assert(metal::is_evaluable<evaluable, void, void*>::value, "");

    static_assert(!metal::is_evaluable<not_evaluable>::value, "");
    static_assert(!metal::is_evaluable<not_evaluable, void>::value, "");
    static_assert(!metal::is_evaluable<not_evaluable, void, void*>::value, "");
    /// [is_evaluable]
}

METAL_ASSERT((not_<is_evaluable<test::alias>>));
METAL_ASSERT((not_<is_evaluable<test::empty>>));
METAL_ASSERT((not_<is_evaluable<test::call>>));
METAL_ASSERT((is_evaluable<test::evaluable>));
METAL_ASSERT((is_evaluable<test::evaluable_union>));


METAL_ASSERT((not_<is_evaluable<test::alias, test::a>>));
METAL_ASSERT((not_<is_evaluable<test::empty, test::a>>));
METAL_ASSERT((not_<is_evaluable<test::call, test::a>>));
METAL_ASSERT((is_evaluable<test::evaluable, test::a>));
METAL_ASSERT((is_evaluable<test::evaluable_union, test::a>));

METAL_ASSERT((not_<is_evaluable<test::alias, test::a, test::b>>));
METAL_ASSERT((not_<is_evaluable<test::empty, test::a, test::b>>));
METAL_ASSERT((not_<is_evaluable<test::call, test::a, test::b>>));
METAL_ASSERT((is_evaluable<test::evaluable, test::a, test::b>));
METAL_ASSERT((is_evaluable<test::evaluable_union, test::a, test::b>));
