/*
//@HEADER
// ************************************************************************
//
// containers_has_static_method_do_update_two_terms.hpp
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

#ifndef CONTAINERS_HAS_STATIC_METHOD_DO_UPDATE_TWO_TERMS_HPP_
#define CONTAINERS_HAS_STATIC_METHOD_DO_UPDATE_TWO_TERMS_HPP_

namespace pressio{ namespace containers{ namespace meta {

/*
  detect if type T has a static method of the form:

  static void do_update(T1 &      , scalar_type,
			const T2 &, scalar_type,
			const T3 &, scalar_type)
 */

template <
  typename T,
  typename scalar_t,
  typename T1,
  typename T2,
  typename T3,
  typename = void
  >
struct has_static_method_do_update_two_terms : std::false_type{};

template <
  typename T,
  typename sc_t,
  typename T1,
  typename T2,
  typename T3
  >
struct has_static_method_do_update_two_terms<
  T, sc_t, T1, T2, T3,
  mpl::enable_if_t<
    std::is_void<
      decltype
      (
       T::do_update
       (
	std::declval< T1 & >(),
	std::declval<const sc_t>(),
	std::declval<const T2 &>(),
	std::declval<const sc_t>(),
	std::declval<const T3 &>(),
	std::declval<const sc_t>()
	)
       )
      >::value
    and
    std::is_void<
      decltype
      (
       T::do_update
       (
	std::declval< T1 & >(),
	std::declval<const T2 &>(),
	std::declval<const sc_t>(),
	std::declval<const T3 &>(),
	std::declval<const sc_t>()
	)
       )
      >::value
    >
  > : std::true_type{};


// template <
//   typename T,
//   typename sc_t,
//   typename T1,
//   typename T2,
//   typename T3
//   >
// struct has_static_method_do_update_two_terms<
//   T, sc_t, T1, T2, T3,
//   mpl::enable_if_t<
//     std::is_void<
//       decltype
//       (
//        T::do_update
//        (
// 	std::declval< T1 & >(),
// 	std::declval<const T2 &>(),
// 	std::declval<const sc_t>(),
// 	std::declval<const T3 &>(),
// 	std::declval<const sc_t>()
// 	)
//        )
//       >::value
//     >
//   > : std::true_type{};

}}} // namespace pressio::containers::meta
#endif
