// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef METAL_NUMBER_ARITHMETIC_DEC_HPP
#define METAL_NUMBER_ARITHMETIC_DEC_HPP

#include <metal/number/number.hpp>

namespace metal
{
    template<typename x>
    struct dec;

    template<typename x>
    using dec_t = typename dec<x>::type;

    template<typename x, x xv>
    struct dec<number<x, xv>> :
            number<x, static_cast<x>(xv - 1)>
    {};
}

#endif
