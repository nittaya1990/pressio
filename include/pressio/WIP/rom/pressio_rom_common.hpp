/*
//@HEADER
// ************************************************************************
//
// pressio_rom_common.hpp
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

#ifndef ROM_PRESSIO_ROM_COMMON_HPP_
#define ROM_PRESSIO_ROM_COMMON_HPP_

/*
   NOTE that the order below matters!
   - Includes are ordered properly to avoid a tangled system.
   - don't rely on files inside impl, these might change

   NOTE also that this header by itself means nothing and if you use
   it as such, you need to know what you are doing.
   This header is here to help the "public" includes named
   "pressio_rom_bla.hpp" inside the pressio/packages directory.
   Users of pressio should NOT rely on this file, but only
   on the top-level "pressio_rom_{lspg,galerkin,wls}.hpp".
*/

//----------------------------------------------
// need forward declarations
#include "rom_fwd.hpp"

//----------------------------------------------
// common predicates
#include "./predicates/decoder/rom_has_const_apply_mapping_accept_operand_result_return_void.hpp"
#include "./predicates/decoder/rom_has_const_get_reference_to_jacobian.hpp"
#include "./predicates/decoder/rom_has_const_update_jacobian_method_accept_operand_return_void.hpp"
#include "./predicates/decoder/rom_has_nonconst_update_jacobian_method_accept_operand_return_void.hpp"

// #include "./masking_methods/rom_has_const_apply_mask_method_accept_operand_result_return_void.hpp"
// #include "./masking_methods/rom_has_const_apply_mask_method_accept_operand_time_result_return_void.hpp"
// #include "./masking_methods/rom_has_const_create_apply_mask_result_method_accept_operand_return_result.hpp"
// #include "./preconditioning_methods/rom_has_const_apply_preconditioner_method_accept_state_time_result_return_void.hpp"
// #include "./preconditioning_methods/rom_has_const_apply_preconditioner_method_accept_state_result_return_void.hpp"
// #include "./residual_methods/rom_has_const_create_residual_method_return_result.hpp"
// #include "./residual_methods/rom_has_const_residual_method_accept_state_result_return_void.hpp"
// #include "./apply_jacobian_methods/rom_has_const_create_apply_jacobian_result_method_accept_operand_return_result.hpp"
// #include "./apply_jacobian_methods/rom_has_const_apply_jacobian_method_accept_state_operand_time_result_return_void.hpp"
// #include "./apply_jacobian_methods/rom_has_const_apply_jacobian_method_accept_state_operand_result_return_void.hpp"
// #include "./apply_discrete_time_jacobian_methods/rom_has_const_apply_discrete_time_jacobian_method_accept_step_time_dt_operand_result_n_states_returning_void.hpp"
// #include "./apply_discrete_time_jacobian_methods/rom_has_const_create_apply_discrete_time_jacobian_result_method_accept_operand_return_result.hpp"
// #include "./galerkin_projector/rom_has_const_apply_method_accept_operand_result_return_void.hpp"


//----------------------------------------------
// common constraints (depend on predicates)
#include "./constraints/rom_decoder_jacobian.hpp"
#include "./constraints/rom_decoder.hpp"
// #include "./constraints/system/rom_steady_system_with_user_provided_apply_jacobian.hpp"
// #include "./constraints/system/rom_discrete_time_system_with_user_provided_apply_jacobian.hpp"
// #include "./constraints/system/rom_continuous_time_system_without_user_provided_apply_jacobian.hpp"
// #include "./constraints/system/rom_continuous_time_system_with_user_provided_apply_jacobian.hpp"
// #include "./constraints/system/rom_continuous_time_system_with_at_least_velocity.hpp"
// #include "./constraints/system/rom_continuous_time_system.hpp"
// #include "./constraints/system/rom_most_likely_continuous_time_system.hpp"
// #include "./constraints/system/rom_most_likely_discrete_time_system.hpp"
// #include "./constraints/system/rom_most_likely_steady_system.hpp"

//----------------------------------------------
// decoder classes (depend on constraints)
#include "./decoder/rom_linear_decoder.hpp"

// //----------------------------------------------
// // fom states management classes (depend on the decoder)
// #include "./fom_states_management/rom_manager_fom_states_static.hpp"
// #include "./fom_states_management/rom_reconstructor_fom_state.hpp"
// #include "./fom_states_management/impl/rom_fom_state_reconstructor_helper.hpp"

#endif  // ROM_PRESSIO_ROM_COMMON_HPP_
