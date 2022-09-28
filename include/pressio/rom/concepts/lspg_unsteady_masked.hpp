/*
//@HEADER
// ************************************************************************
//
// rom_fom_system_continuous_time.hpp
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

#ifndef ROM_CONSTRAINTS_ROM_UNSTEADY_LSPG_MASKED_HPP_
#define ROM_CONSTRAINTS_ROM_UNSTEADY_LSPG_MASKED_HPP_

#include "helpers.hpp"

#ifdef PRESSIO_ENABLE_CXX20

// this is here so that we can clearly show it in the
// doc via rst literal include directive
namespace pressio{ namespace rom{ namespace lspg{ namespace unsteady{

template <class TrialSubspaceType, class FomSystemType, class MaskerType>
concept ComposableIntoMaskedProblem =
     SemiDiscreteFomWithJacobianAction<FomSystemType, typename TrialSubspaceType::basis_matrix_type>
  && ComposableIntoDefaultProblem<TrialSubspaceType, FomSystemType>

  && MaskableWith<typename FomSystemType::right_hand_side_type, MaskerType>
  && MaskableWith<
       concepts::impl::fom_jacobian_action_on_trial_space_t<FomSystemType, TrialSubspaceType>,
       MaskerType>;

}}}} //end namespace pressio::rom::lspg::unsteady

// #else

// namespace pressio{ namespace rom{ namespace lspg{ namespace unsteady{

// template<class T, class MaskerType, class TrialSubspaceType, class enable = void>
// struct MaskableWith : std::false_type{};

// template<class T, class MaskerType, class TrialSubspaceType>
// struct MaskableWith<
//   T, MaskerType, TrialSubspaceType,
//   mpl::enable_if_t<
//        SemiDiscreteFomWithJacobianAction<T, TrialSubspaceType>::value
//     && PossiblyAffineTrialColumnSubspace<TrialSubspaceType>::value
//     //
//     && std::is_copy_constructible<
// 	 decltype(std::declval<MaskerType const &>().
// 	           createApplyMaskResult( std::declval<typename T::right_hand_side_type const &>() )
// 	         )
//       >::value
//    >
//   > : std::true_type{};

// }}}}

#endif
#endif  // ROM_CONSTRAINTS_ROM_FOM_SYSTEM_CONTINUOUS_TIME_HPP_
