// Copyright Bruno Dutra 2015-2016
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt

#ifndef METAL_LIST_REVERSE_HPP
#define METAL_LIST_REVERSE_HPP

#include <metal/list/size.hpp>
#include <metal/list/slice.hpp>
#include <metal/number/number.hpp>
#include <metal/number/dec.hpp>

namespace metal
{
    /// \ingroup list
    /// ...
    template<typename seq>
    using reverse = slice<seq, dec<size<seq>>, size<seq>, int_<-1>>;
}

#endif
