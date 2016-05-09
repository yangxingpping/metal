// Copyright Bruno Dutra 2015-2016
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#ifndef METAL_LIST_POP_BACK_HPP
#define METAL_LIST_POP_BACK_HPP

#include <metal/list/size.hpp>
#include <metal/list/slice.hpp>
#include <metal/number/if.hpp>
#include <metal/number/not.hpp>
#include <metal/number/sub.hpp>
#include <metal/number/cast.hpp>
#include <metal/number/less.hpp>
#include <metal/number/number.hpp>

namespace metal
{
    /// \ingroup list
    /// ...
    template<typename seq, typename n = metal::size_t<1>>
    using pop_back = slice<
        seq,
        sub<n, n>,
        if_<
            not_<less<size<seq>, cast<n, std::size_t>>>,
            sub<size<seq>, n>
        >
    >;
}

#endif
