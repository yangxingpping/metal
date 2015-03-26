// Copyright Bruno Dutra 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/mpl2/core/integral.hpp>
#include <boost/mpl2/core/tag.hpp>
#include <boost/mpl2/core/assert.hpp>
#include <boost/mpl2/core/comparison/equal.hpp>

#include <boost/config.hpp>
#include <climits>

template<typename integral>
bool test_integral(integral const& constant)
{
    using boost::mpl2::tag;
    using boost::mpl2::equal;
    using boost::mpl2::bool_;

    BOOST_MPL2_ASSERT((equal<typename tag<typename integral::type>::type, typename tag<integral>::type>));
    BOOST_MPL2_ASSERT((equal<typename integral::type::value_type, typename integral::value_type>));
    BOOST_MPL2_ASSERT(bool_<integral::type::value == integral::value>);

    return integral::value == constant;
}

#if !defined(SIZE_MAX)
    #define SIZE_MAX static_cast<std::size_t>(-1)
#endif

int main()
{
    return  !test_integral(boost::mpl2::true_())                    ||
            !test_integral(boost::mpl2::false_())                   ||
            !test_integral(boost::mpl2::bool_<true>())              ||
            !test_integral(boost::mpl2::bool_<false>())             ||
            !test_integral(boost::mpl2::char_<' '>())               ||
            !test_integral(boost::mpl2::uchar_<255>())              ||
            !test_integral(boost::mpl2::schar_<SCHAR_MIN>())        ||
            !test_integral(boost::mpl2::wchar_t_<L' '>())           ||
#if !defined(BOOST_NO_CXX11_CHAR16_T)
            !test_integral(boost::mpl2::wchar_t_<u' '>())           ||
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
            !test_integral(boost::mpl2::wchar_t_<U' '>())           ||
#endif
            !test_integral(boost::mpl2::short_<SHRT_MIN>())         ||
            !test_integral(boost::mpl2::ushort_<USHRT_MAX>())       ||
            !test_integral(boost::mpl2::int_<INT_MIN>())            ||
            !test_integral(boost::mpl2::uint_<UINT_MAX>())          ||
            !test_integral(boost::mpl2::long_<LONG_MIN>())          ||
            !test_integral(boost::mpl2::ulong_<ULONG_MAX>())        ||
#if !defined(BOOST_NO_LONG_LONG)
            !test_integral(boost::mpl2::long_long_<LONG_MIN>())     ||
            !test_integral(boost::mpl2::ulong_long_<ULONG_MAX>())   ||
#endif
            !test_integral(boost::mpl2::size_t_<SIZE_MAX>());
}
