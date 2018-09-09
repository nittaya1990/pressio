#ifndef SOLVERS_EXPERIMENTAL_POLICY_NONLINEAR_ITERATIVE_HPP
#define SOLVERS_EXPERIMENTAL_POLICY_NONLINEAR_ITERATIVE_HPP

#include <iostream>
#include <type_traits>

#include "solvers_types.hpp"
#include "solvers_linear_factory.hpp"
#include "system_traits.hpp"
#include "solvers_meta_static_checks.hpp"


namespace solvers {


struct SolversNonLinearIterativeNewtonRaphsonPolicy {  

  template <
    typename SolverT,
    typename PrecT,
    typename NormT,
    typename SystemT,
    typename VectorT,
    typename std::enable_if<
      !solvers::meta::are_vector_compatible<
        typename details::system_traits<SystemT>::vector_type,
        VectorT
      >::value,
      int
    >::type* = nullptr
  >
  static auto solve(
    const SystemT& system, 
    const VectorT& x0,
    uint maxIterations, 
    uint maxNonLinearIterations,
    double tolerance,
    double nonLinearTolerance
  ) {

    std::cerr << "Error: the type of the RHS vector is not compatible with the provided nonlinear system" << std::endl;
    assert(0);

  	return x0;
  }


  template <
    typename SolverT,
    typename PrecT,
    typename NormT,
    typename SystemT,
    typename VectorT,
    typename std::enable_if<
      solvers::meta::are_vector_compatible<
        typename details::system_traits<SystemT>::vector_type,
        VectorT
      >::value,
      int
    >::type* = nullptr
  >
  static auto solve(
    const SystemT& sys, 
    const VectorT& x0, 
    uint maxIterations, 
    uint maxNonLinearIterations, 
    double tolerance, 
    double nonLinearTolerance
  ) {
  	
    auto dy = sys.residual(x0);
    auto Ja = sys.jacobian(x0);

    auto solver = LinearSolvers::createIterativeSolver<SolverT, typename SystemT::matrix_type, PrecT>(Ja);
    solver.setMaxIterations(maxIterations);
    solver.setTolerance(tolerance);

    uint iStep = 1;
    auto xOld = x0;
    auto xNew = x0 - solver.solve(dy);

    while (iStep++ < maxNonLinearIterations && NormT::template compute_norm_difference(xOld, xNew) > nonLinearTolerance) {      
        xOld = xNew;
        dy = sys.residual(xNew);
        Ja = sys.jacobian(xNew);

        solver.resetLinearSystem(Ja);
        xNew = xNew - solver.solve(dy);
      }

    return xNew;
  }

};

} // end namespace solvers

#endif
