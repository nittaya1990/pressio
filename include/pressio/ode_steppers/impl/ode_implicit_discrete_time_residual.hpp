/*
//@HEADER
// ************************************************************************
//
// ode_implicit_discrete_time_residual.hpp
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

#ifndef ODE_STEPPERS_IMPL_ODE_IMPLICIT_DISCRETE_TIME_RESIDUAL_HPP_
#define ODE_STEPPERS_IMPL_ODE_IMPLICIT_DISCRETE_TIME_RESIDUAL_HPP_

namespace pressio{ namespace ode{ namespace impl{

/*
  BDF1 residual: R(y_n+1) = y_n+1 - y_n - dt*f(t_n+1, y_n+1)

  - on input R contains the application RHS: R = f(t_n+1, y_n+1, ...)
  - on output, R contains the time-discrete residual
*/
template <
  typename StateType,
  typename ResidualType,
  typename StencilStatesContainerType,
  typename ScalarType
  >
void discrete_time_residual(const StateType & y_np1,
			    ResidualType & R,
			    const StencilStatesContainerType & stencilStates,
			    const ScalarType & dt,
			    ::pressio::ode::BDF1)
{
  constexpr auto cnp1 = ::pressio::ode::constants::bdf1<ScalarType>::c_np1_;
  constexpr auto cn   = ::pressio::ode::constants::bdf1<ScalarType>::c_n_;
  const auto cf	      = ::pressio::ode::constants::bdf1<ScalarType>::c_f_ * dt;
  ::pressio::ops::update(R, cf,
			 y_np1, cnp1,
			 stencilStates(::pressio::ode::n()), cn);
}

/*
  BDF2 residual: R(y_n+1) = y_n+1 - (4/3)*y_n + (1/3)*y_n-1 - (2/3)*dt*f(t_n+1, y_n+1)

  - on input R contains the application RHS: R = f(t_n+1, y_n+1, ...)
  - on output, R contains the time-discrete residual
*/
template <
  typename StateType,
  typename ResidualType,
  typename StencilStatesContainerType,
  typename ScalarType
  >
void discrete_time_residual(const StateType	& y_np1,
			    ResidualType & R,
			    const StencilStatesContainerType & stencilStates,
			    const ScalarType & dt,
			    ::pressio::ode::BDF2)
{
  using nm1 = ode::nMinusOne;
  constexpr auto cnp1 = ::pressio::ode::constants::bdf2<ScalarType>::c_np1_;
  constexpr auto cn   = ::pressio::ode::constants::bdf2<ScalarType>::c_n_;
  constexpr auto cnm1 = ::pressio::ode::constants::bdf2<ScalarType>::c_nm1_;
  const auto cf	      = ::pressio::ode::constants::bdf2<ScalarType>::c_f_ * dt;

  ::pressio::ops::update(R, cf,
                         y_np1, cnp1,
			 stencilStates(::pressio::ode::n()), cn,
			 stencilStates(nm1()), cnm1);
}

/*
  CrankNicolson residual:
  R(y_n+1) = y_n+1 - y_n - 0.5*dt*[ f(t_n+1, y_n+1) + f(t_n, y_n) ]

  - Note that on entry, R does not contain anything, should be fully overwritten
  - stencilStates contain: y_n
  - stencilVelocities contain f_n, f_n+1
*/
template <
  typename StateType,
  typename ResidualType,
  typename StencilStatesContainerType,
  typename StencilVelocitiesContainerType,
  typename ScalarType
  >
void discrete_time_residual(const StateType & y_np1,
			    ResidualType & R,
			    const StencilStatesContainerType & stencilStates,
			    const StencilVelocitiesContainerType & stencilVelocities,
			    const ScalarType & dt,
			    ::pressio::ode::CrankNicolson)
{
  using cnst = ::pressio::ode::constants::cranknicolson<ScalarType>;
  constexpr auto cnp1  = cnst::c_np1_;
  constexpr auto cn    = cnst::c_n_;
  constexpr auto cfn   = cnst::c_fn_;
  const auto cfnDt   = cfn*dt;
  const auto cfnp1Dt = cfn*dt;

  constexpr auto zero  = ::pressio::utils::Constants<ScalarType>::zero();
  ::pressio::ops::update(R, zero,
			 y_np1, cnp1,
			 stencilStates(::pressio::ode::n()), cn,
			 stencilVelocities(::pressio::ode::n()), cfnDt,
			 stencilVelocities(::pressio::ode::nPlusOne()), cfnp1Dt);
}

}}}//end namespace pressio::ode::impl
#endif  // ODE_STEPPERS_IMPL_ODE_IMPLICIT_DISCRETE_TIME_RESIDUAL_HPP_
