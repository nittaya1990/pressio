
#ifndef ROM_EVALUATE_FOM_RHS_STEADY_HPP_
#define ROM_EVALUATE_FOM_RHS_STEADY_HPP_

namespace rompp{ namespace rom{ namespace policy{

template <>
struct EvaluateFomRhsDefault<true>{

  template <
    typename fom_t,
    typename state_t,
    typename rhs_t
    >
  void evaluate(const fom_t	& fomObj,
		const state_t & yFOM,
		rhs_t		& rhs) const{
    fomObj.residual(*yFOM.data(), *rhs.data());
  }

  template <
    typename fom_t,
    typename state_t
    >
  auto evaluate(const fom_t	& fomObj,
		const state_t & yFOM) const
    -> decltype(fomObj.residual(*yFOM.data())){
    return fomObj.residual(*yFOM.data());
  }

};

}}} //end namespace rompp::rom::policy
#endif
