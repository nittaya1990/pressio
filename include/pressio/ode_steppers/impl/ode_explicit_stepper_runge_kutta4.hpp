/*
//@HEADER
// ************************************************************************
//
// ode_explicit_runge_kutta4_stepper_impl.hpp
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

#ifndef ODE_EXPLICIT_IMPL_ODE_EXPLICIT_RUNGE_KUTTA4_STEPPER_IMPL_HPP_
#define ODE_EXPLICIT_IMPL_ODE_EXPLICIT_RUNGE_KUTTA4_STEPPER_IMPL_HPP_

#include <array>

namespace pressio{ namespace ode{ namespace impl{

template<
  class ScalarType,
  class StateType,
  class SystemType,
  class VelocityType
  >
class ExplicitRungeKutta4Stepper
{
public:
  static constexpr bool is_implicit = false;
  static constexpr bool is_explicit = true;
  static constexpr stepper_order_type order_value = 4;

private:
  ::pressio::utils::InstanceOrReferenceWrapper<SystemType> systemObj_;
  std::array<VelocityType, 4> velocities_;
  StateType auxiliaryState_;

public:
  ExplicitRungeKutta4Stepper() = delete;
  ExplicitRungeKutta4Stepper(const ExplicitRungeKutta4Stepper & other) = default;
  ExplicitRungeKutta4Stepper & operator=(const ExplicitRungeKutta4Stepper & other) = delete;
  ExplicitRungeKutta4Stepper(ExplicitRungeKutta4Stepper && other)  = default;
  ExplicitRungeKutta4Stepper & operator=(ExplicitRungeKutta4Stepper && other)  = delete;
  ~ExplicitRungeKutta4Stepper() = default;

  ExplicitRungeKutta4Stepper(const StateType & state,
                                 SystemType && systemObj)
    : systemObj_(std::forward<SystemType>(systemObj)),
      velocities_{systemObj.createVelocity(),
                  systemObj.createVelocity(),
                  systemObj.createVelocity(),
                  systemObj.createVelocity()},
      auxiliaryState_{::pressio::ops::clone(state)}
  {}

public:
  stepper_order_type order() const
  {
    return order_value;
  }

  template<class StepCountType>
  void operator()(StateType & odeSolution,
  	      const ScalarType & t,
  	      const ScalarType & dt,
  	      const StepCountType & step)
  {
    PRESSIOLOG_DEBUG("rk4 stepper: do step");

    auto & rhs0 = velocities_[0];
    auto & rhs1 = velocities_[1];
    auto & rhs2 = velocities_[2];
    auto & rhs3 = velocities_[3];

    constexpr auto two  = ::pressio::utils::Constants<ScalarType>::two();
    constexpr auto three  = ::pressio::utils::Constants<ScalarType>::three();
    constexpr auto six  = two * three;

    const ScalarType dt_half = dt / two;
    const ScalarType t_phalf = t + dt_half;
    const ScalarType dt6 = dt / six;
    const ScalarType dt3 = dt / three;

    // stage 1: ytmp = y + rhs0*dt_half;
    systemObj_.get().velocity(odeSolution, t, rhs0);
    this->stage_update_impl(auxiliaryState_, odeSolution, rhs0, dt_half);

    // stage 2: ytmp = y + rhs1*dt_half;
    systemObj_.get().velocity(auxiliaryState_, t_phalf, rhs1);
    this->stage_update_impl(auxiliaryState_, odeSolution, rhs1, dt_half);

    // stage 3: ytmp = y + rhs2*dt;
    systemObj_.get().velocity(auxiliaryState_, t_phalf, rhs2);
    this->stage_update_impl(auxiliaryState_, odeSolution, rhs2, dt);

    // stage 4: y_n += dt/6 * ( k1 + 2 * k2 + 2 * k3 + k4 )
    systemObj_.get().velocity(auxiliaryState_,  t + dt, rhs3);
    this->stage_update_impl(odeSolution, rhs0, rhs1, rhs2, rhs3, dt6, dt3);
  }

private:
  template<class rhs_t>
  void stage_update_impl(StateType & yIn,
		    const StateType & stateIn,
		    const rhs_t & rhsIn,
		    ScalarType dtValue)
  {
    constexpr auto zero  = ::pressio::utils::Constants<ScalarType>::zero();
    constexpr auto one  = ::pressio::utils::Constants<ScalarType>::one();
    ::pressio::ops::update(yIn, zero, stateIn, one, rhsIn, dtValue);
  }

  template<class rhs_t>
  void stage_update_impl(StateType & stateIn,
		    const rhs_t & rhsIn0,
        const rhs_t & rhsIn1,
		    const rhs_t & rhsIn2,
        const rhs_t & rhsIn3,
		    ScalarType dt6,
        ScalarType dt3)
  {
    constexpr auto one  = ::pressio::utils::Constants<ScalarType>::one();
    ::pressio::ops::update(stateIn, one,
			   rhsIn0, dt6,
			   rhsIn1, dt3,
			   rhsIn2, dt3,
			   rhsIn3, dt6);
  }
};

}}}//end namespace pressio::ode::explicitmethods::impl
#endif  // ODE_EXPLICIT_IMPL_ODE_EXPLICIT_RUNGE_KUTTA4_STEPPER_IMPL_HPP_
