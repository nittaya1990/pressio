/*
//@HEADER
// ************************************************************************
//
// solvers_lm_gain_factor.hpp
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

#ifndef SOLVERS_NONLINEAR_IMPL_UPDATERS_SOLVERS_LM_GAIN_FACTOR_HPP_
#define SOLVERS_NONLINEAR_IMPL_UPDATERS_SOLVERS_LM_GAIN_FACTOR_HPP_

namespace pressio{ namespace nonlinearsolvers{ namespace impl{

template<typename StateType, class ScalarType>
class LMGainFactor
{
  using scalar_type = ScalarType;
  StateType cDiagH_; // = h * diag(J^T J)
  StateType trialState_;

public:
  LMGainFactor(LMGainFactor const &) = default;
  LMGainFactor & operator=(LMGainFactor const &) = default;
  LMGainFactor(LMGainFactor &&) = default;
  LMGainFactor & operator=(LMGainFactor &&) = default;
  ~LMGainFactor() = default;

  LMGainFactor(const StateType & state)
    : cDiagH_(::pressio::ops::clone(state)), 
      trialState_(::pressio::ops::clone(state))
  {
    constexpr auto zero = ::pressio::utils::Constants<scalar_type>::zero();
    ::pressio::ops::fill(cDiagH_, zero);
    ::pressio::ops::fill(trialState_, zero);
  }

public:
  void resetForNewCall(){
    constexpr auto zero = ::pressio::utils::Constants<scalar_type>::zero();
    ::pressio::ops::fill(cDiagH_, zero);
    ::pressio::ops::fill(trialState_, zero);
  }

  template<typename SystemType, typename SolverMixinType>
  scalar_type compute(const SystemType & system,
		   StateType & state,
		   const scalar_type & mu,
		   SolverMixinType & solverObj)
  {
    constexpr auto zero = ::pressio::utils::Constants<scalar_type>::zero();
    constexpr auto one  = ::pressio::utils::Constants<scalar_type>::one();
    constexpr auto two  = ::pressio::utils::Constants<scalar_type>::two();

    const auto & correction = solverObj.correctionCRef();
    const auto & g	    = solverObj.gradientCRef();
    const auto & H	    = solverObj.hessianCRefBeforeLMDiagonalScaling();

    // denom
    const auto diagH = ::pressio::diag(H);
    ::pressio::ops::elementwise_multiply(one, correction, diagH, zero, cDiagH_);
    const auto den1 = ::pressio::ops::dot(correction, cDiagH_);
    const auto den2 = ::pressio::ops::dot(correction, g);
    const auto denom = (one/two)*(mu*den1 + den2);

    // numerator
    auto norm = solverObj.residualNormCurrentCorrectionStep();
    const auto r2Old = norm*norm;

    ::pressio::ops::update(trialState_, zero, state, one, correction, one);
    solverObj.residualNorm(system, trialState_, norm);

    return (r2Old - norm*norm) / denom;
  }
};

}}}
#endif  // SOLVERS_NONLINEAR_IMPL_UPDATERS_SOLVERS_LM_GAIN_FACTOR_HPP_
