
#ifndef ODE_IMPLICIT_EULER_RESIDUAL_STANDARD_POLICY_HPP_
#define ODE_IMPLICIT_EULER_RESIDUAL_STANDARD_POLICY_HPP_

#include "ode_ConfigDefs.hpp"
#include "./impl/ode_euler_implicit_residual_impl.hpp"
#include "./base/ode_implicit_euler_residual_policy_base.hpp"

namespace ode{
namespace policy{

template<typename state_type, typename residual_type,
	 typename model_type, typename time_type>
class implicitEulerStandardResidual
  : public implicitEulerResidualPolicyBase<
             implicitEulerStandardResidual,state_type,
                 residual_type,model_type, time_type>
{
public:
  implicitEulerStandardResidual() = default;
  ~implicitEulerStandardResidual() = default;  
private:
  // enable if using types from core package
  template <typename U = state_type,
	    typename T = residual_type,
	    typename
	    std::enable_if<
	      core::meta::is_coreVectorWrapper<U>::value==true &&
	      core::meta::is_coreVectorWrapper<T>::value==true
	      >::type * = nullptr
	    >
  void computeImpl(const U & y, const U & ynm1, T & R,
		   model_type & model, time_type t, time_type dt)
  {
    // first eval RHS
    model.residual(*y.data(), *R.data(), t);
    // then fix residual based on time stepping features
    ode::impl::implicit_euler_residual_impl(y, ynm1, R, dt);
  }


  // // enable if using types from core package
  // template <typename U = state_type,
  // 	    typename T = residual_type,
  // 	    typename
  // 	    std::enable_if<
  // 	      core::meta::is_coreVectorWrapper<U>::value==true &&
  // 	      core::meta::is_coreVectorWrapper<T>::value==true
  // 	      >::type * = nullptr
  // 	    >
  // void computeImpl(const U & y0, const U & y,
  // 		   const U & ynm1, T & R,
  // 		   model_type & model,
  // 		   time_type t, time_type dt)
  // {
  //   U yFull = y0 + y;
    
  //   // first eval RHS
  //   model.residual(*yFull.data(), *R.data(), t);
  //   // then fix residual based on time stepping features
  //   ode::impl::implicit_euler_residual_impl(y, ynm1, R, dt);
  // }
  
private:
  friend implicitEulerResidualPolicyBase<implicitEulerStandardResidual,
					 state_type,residual_type,
					 model_type, time_type>;
};
  
}//end namespace polices
}//end namespace ode  
#endif 
