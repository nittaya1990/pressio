/*
//@HEADER
// ************************************************************************
//
// ops_dot.hpp
//                     		  Pressio
//                             Copyright 2019
//    National Technology & Engineering Solutions of Sandia, LLC (NTESS)
//
// Under the terms of Contract DE-NA0003525 with NTESS, the
// U.S. Government retains certain rights in this software.
//
// Pressio is licensed under BSD-3-Clause terms of use:
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Francesco Rizzi (fnrizzi@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef OPS_KOKKOS_OPS_DOT_HPP_
#define OPS_KOKKOS_OPS_DOT_HPP_

#include <KokkosBlas1_dot.hpp>

namespace pressio{ namespace ops{

namespace impl{
template <typename T1, typename T2>
::pressio::mpl::enable_if_t<
  ::pressio::Traits<T1>::package_identifier == PackageIdentifier::Kokkos and
  ::pressio::Traits<T2>::package_identifier == PackageIdentifier::Kokkos,
  typename ::pressio::Traits<T1>::scalar_type
  >
kokkos_ops_dot(const T1 & a,
    const T2 & b)
{
  static_assert
    (are_scalar_compatible<T1, T2>::value, "dot: types are not scalar compatible");
  static_assert
    (have_matching_execution_space<T1, T2>::value,
     "dot: types must have matching execution space");

  static_assert
    (::pressio::Traits<T1>::rank==1 and ::pressio::Traits<T2>::rank==1, 
      "ops::dot only accepts vectors");

  assert(a.extent(0) == b.extent(0));
  return ::KokkosBlas::dot(impl::get_native(a), impl::get_native(b));
}
}//end namespace impl

template <typename T1, typename T2>
::pressio::mpl::enable_if_t<
  ::pressio::Traits<T1>::package_identifier == PackageIdentifier::Kokkos and
  ::pressio::Traits<T2>::package_identifier == PackageIdentifier::Kokkos,
  typename ::pressio::Traits<T1>::scalar_type
  >
dot(const T1 & a,
    const T2 & b)
{
  return impl::kokkos_ops_dot(a,b);
}

template <typename T1, typename T2>
::pressio::mpl::enable_if_t<
  ::pressio::Traits<T1>::package_identifier == PackageIdentifier::Kokkos and
  ::pressio::Traits<T2>::package_identifier == PackageIdentifier::Kokkos
  >
dot(const T1 & a,
    const T2 & b,
    typename ::pressio::Traits<T1>::scalar_type & result)
{
  result = impl::kokkos_ops_dot(a,b);
}


}}//end namespace pressio::ops
#endif  // OPS_KOKKOS_OPS_DOT_HPP_
