//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#include <boost/simd/function/div.hpp>
#include <boost/simd/pack.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <simd_test.hpp>

namespace bs = boost::simd;

template <typename T, std::size_t N, typename Env>
void test(Env& runtime)
{
  using p_t = bs::pack<T, N>;

  T a1[N], a2[N], b[N];
  a1[0] = a2[0] = T(0); // suppress a warning !?
  for(std::size_t i = 0; i < N; ++i)
  {
    a1[i] = (i%2) ? T(1+i) : T(3+i);
    a2[i] = (i%2) ? T(i+N) : T(2*i+1);
    b[i] = bs::div(bs::round,a1[i], a2[i]);
  }

  p_t aa1(&a1[0], &a1[N]);
  p_t aa2(&a2[0], &a2[N]);
  p_t bb(&b[0], &b[N]);

  STF_IEEE_EQUAL(bs::div(bs::round,aa1, aa2), bb);
}

STF_CASE_TPL("Check divround on pack" , STF_NUMERIC_TYPES)
{
  static const std::size_t N = bs::pack<T>::static_size;

  test<T, N>(runtime);
  test<T, N/2>(runtime);
  test<T, N*2>(runtime);
}