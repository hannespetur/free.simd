//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_SIN_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/simd/arch/common/detail/scalar/trigo.hpp>
#include <boost/simd/function/restricted.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sin_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_MAYBEINLINE A0 operator() (const std_tag &, A0 a0) const BOOST_NOEXCEPT
    {
      return std::sin(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( sin_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_MAYBEINLINE A0 operator() ( A0  a0) const BOOST_NOEXCEPT
    {
      return detail::trig_base<A0,tag::radian_tag,tag::not_simd_type,tag::big_tag>::sina(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( sin_
                          , (typename A0, typename A1)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_ < bd::unspecified_<A1> >
                          )
  {
    BOOST_MAYBEINLINE A0 operator() ( A0  a0,  A1 ) const BOOST_NOEXCEPT
    {
      return detail::trig_base<A0,tag::radian_tag,tag::not_simd_type,A1>::sina(a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( sin_
                          , (typename A0)
                          , bd::cpu_
                          , bs::restricted_tag
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_MAYBEINLINE A0 operator() (const restricted_tag &,  A0  a0) const BOOST_NOEXCEPT
    {
      return detail::trig_base<A0,tag::radian_tag,tag::not_simd_type,tag::clipped_pio4_tag>::sina(a0);
    }
  };

} } }


#endif

