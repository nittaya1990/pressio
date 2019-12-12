/*
//@HEADER
// ************************************************************************
//
// solvers_hessian_helper_policy.hpp
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

#ifndef SOLVERS_IMPL_HESSIAN_APPROX_HELPERS_POLICY_HPP
#define SOLVERS_IMPL_HESSIAN_APPROX_HELPERS_POLICY_HPP

#include "../../solvers_ConfigDefs.hpp"
#include "../../../../CONTAINERS_OPS"

namespace pressio{ namespace solvers{ namespace iterative{ namespace impl{

template<typename J_t, typename enable = void>
struct HessianApproxHelper;


// when J is matrix wrapper, the hessian J^T*J
// is computed by doing product of J^T*J
template<typename J_t>
struct HessianApproxHelper<
  J_t,
  ::pressio::mpl::enable_if_t<
    ::pressio::containers::meta::is_matrix_wrapper<J_t>::value
    >
  >
{

  template <typename result_t>
  static void evaluate(J_t & J, result_t & result){
    constexpr bool transposeJ = true;
    ::pressio::containers::ops::product<J_t, J_t, result_t,
				transposeJ>(J, J, result);
  }

  template <typename result_t>
  static result_t evaluate(J_t & J){
    return ::pressio::containers::ops::product<J_t, J_t, result_t, true>(J, J);
  }
};


/* when J is multivector wrapper, the hessian J^T*J
 * is computed by doing the J self_dot J
 * in some cases, the impl of self dot leverages symmetry of the result,
 * so self_dot computes only half of the result matrix and fills the rest by symmetry
 */
template<typename J_t>
struct HessianApproxHelper<
  J_t,
  ::pressio::mpl::enable_if_t<
    containers::meta::is_multi_vector_wrapper<J_t>::value
    >
  >
{

  template <typename result_t>
  static void evaluate(J_t & J, result_t & result) {
    ::pressio::containers::ops::dot_self(J, result);
  }

  template <typename result_t>
  static result_t evaluate(J_t & J){
    return ::pressio::containers::ops::dot_self<J_t, result_t>(J);
  }
};

}}}} //end namespace pressio::solvers::iterative::impl
#endif
