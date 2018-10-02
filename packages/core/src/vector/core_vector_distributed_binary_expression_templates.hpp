
#ifndef CORE_VECTOR_VECTOR_DISTRIBUTED_BINARY_EXPRESSION_TEMPLATES_HPP_
#define CORE_VECTOR_VECTOR_DISTRIBUTED_BINARY_EXPRESSION_TEMPLATES_HPP_

#include "core_vector_meta.hpp"

namespace rompp{
namespace core{
namespace exprtemplates{
  
template <typename der_t>
class DistributedVecExpressionBase {
  DistributedVecExpressionBase() = default;
  ~DistributedVecExpressionBase() = default;
  friend der_t;
public:
  static constexpr bool is_shared_mem = false;
  static constexpr bool is_vector_expression = true;
};
///-----------------------------------------------------


///-----------------------------------------------------
///-----------------------------------------------------
template <typename T,
	  typename enable = void>
struct is_distributed_vector_expression : std::false_type{};

template <typename T>
struct is_distributed_vector_expression<T,
      core::meta::enable_if_t<
       core::meta::publicly_inherits_from<
	T,DistributedVecExpressionBase<T>
	 >::value
	>> : std::true_type{};

template <typename T,
	  typename enable = void>
struct is_admissible_vec_for_dist_expression : std::false_type{};

template <typename T>
struct is_admissible_vec_for_dist_expression<T,
      core::meta::enable_if_t<
	core::meta::is_core_vector_wrapper<T>::value &&
	!core::details::traits<T>::is_shared_mem
      >> : std::true_type{};
  
///-----------------------------------------------------
///-----------------------------------------------------

  
  
//----------------------------------------------------
// default 
template <typename OP_t, typename T1,
	  typename T2, typename value_t,
	  typename LO_t, typename enable = void>
class DistributedVectorBinaryExp
  : public DistributedVecExpressionBase<
  DistributedVectorBinaryExp<OP_t,T1,T2,value_t,LO_t>>{

  const T1 & a_;
  const T2 & b_;
  OP_t op_;
  using this_t = DistributedVectorBinaryExp<OP_t,T1,T2,value_t,LO_t>;
  friend DistributedVecExpressionBase<this_t>;

 public:
  using sc_type = value_t;
  using LO_type = LO_t;    

  DistributedVectorBinaryExp(T1 const& a, T2 const& b)
    : a_(a), b_(b){}
  ~DistributedVectorBinaryExp() = default;

  value_t operator()(size_t i) const {
    return op_(a_(i), b_(i));}

  LO_t localSize() const {
    return a_.localSize();}
};

  
//----------------------------------------------------  
// T1: whatever, T2: vector
template <typename OP_t, typename T1, typename T2,
	  typename value_t, typename LO_t>
class DistributedVectorBinaryExp<
         OP_t, T1, T2, value_t, LO_t,
	 core::meta::enable_if_t<
	   !std::is_scalar<T1>::value &&
	   core::meta::is_core_vector_wrapper<T2>::value &&
	   !core::details::traits<T2>::is_shared_mem>
  >
  : public DistributedVecExpressionBase<
  DistributedVectorBinaryExp<OP_t,T1,T2,value_t,LO_t>>{

  const T1 & a_;
  const T2 & b_;
  OP_t op_;
  using this_t = DistributedVectorBinaryExp<OP_t,T1,T2,value_t,LO_t>;
  friend DistributedVecExpressionBase<this_t>;

public:
  using sc_type = value_t;
  using LO_type = LO_t;
    
  DistributedVectorBinaryExp(T1 const& a, T2 const& b)
    : a_(a), b_(b){}
  ~DistributedVectorBinaryExp() = default;

  value_t operator()(size_t i) const {
    return op_(a_(i), b_(i));}

  LO_t localSize() const {
    return b_.localSize();}
};


//-----------------------------------------------------
// T1: not scalar, T2: scalar 
template <typename OP_t, typename T1,
	    typename value_t, typename LO_t>
class DistributedVectorBinaryExp<
         OP_t, T1, value_t, value_t, LO_t,
	 core::meta::enable_if_t<
	   !std::is_scalar<T1>::value &&
	   std::is_scalar<value_t>::value
	   > >
  : public DistributedVecExpressionBase<
  DistributedVectorBinaryExp<OP_t,T1,value_t,value_t,LO_t>>{

  const T1 & a_;
  value_t b_;
  OP_t op_;
  using th_t = DistributedVectorBinaryExp<OP_t,T1,value_t,value_t,LO_t>;
  friend DistributedVecExpressionBase<th_t>;

public:
  using sc_type = value_t;
  using LO_type = LO_t;
    
  DistributedVectorBinaryExp(const T1 & a, value_t b)
    : a_(a), b_(b){}
  ~DistributedVectorBinaryExp() = default;

  value_t operator()(size_t i) const {
    return op_(a_(i), b_);}

  LO_t localSize() const{
    return a_.localSize();}
};
//-----------------------------------------------------
  
  

}//end namespace exprtemplates
}//end namespace core
}//end namespace rompp
#endif
