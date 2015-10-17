// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef METAL_MAP_AT_KEY_HPP
#define METAL_MAP_AT_KEY_HPP

namespace metal
{
    /// \ingroup map
    /// \brief ...
    template<typename map, typename key>
    struct at_key;

    /// \ingroup map
    /// \brief Eager adaptor for \ref at_key.
    template<typename map, typename key>
    using at_key_t = typename at_key<map, key>::type;
}

#include <metal/map/map.hpp>
#include <metal/list/list.hpp>
#include <metal/core/inherit.hpp>
#include <metal/optional/conditional.hpp>
#include <metal/optional/just.hpp>
#include <metal/optional/nothing.hpp>

namespace metal
{
    namespace detail
    {
        template<typename key, typename val>
        just<val> lookup(list<key, val>*);

        template<typename>
        nothing lookup(...);

        template<typename>
        struct hash
        {
            static constexpr void* const value = 0;
        };

        template<
            template<typename...> class map,
            template<typename...> class... pairs,
            typename... keys,
            typename... vals
        >
        struct hash<map<pairs<keys, vals>...>>
        {
            static constexpr inherit<list<keys, vals>...>* const value = 0;
        };
    }

    template<typename map, typename key>
    struct at_key;

    template<typename map, typename key>
    struct at_key:
        conditional<
            is_map_t<map>,
            decltype(detail::lookup<key>(detail::hash<map>::value))
        >
    {};
}

#endif
