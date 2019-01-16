
#ifndef CORE_EIGEN_SPARSE_MAT_PRODUCT_EIGEN_DENSE_MAT_HPP_
#define CORE_EIGEN_SPARSE_MAT_PRODUCT_EIGEN_DENSE_MAT_HPP_

#include "../core_ops_meta.hpp"
#include "../../matrix/core_matrix_meta.hpp"
#include "core_eigen_mat_mat_impl.hpp"

namespace rompp{ namespace core{ namespace ops{

/*---------------------------------------------------------
C = A B
- A is sparse matrix from eigen
- B is dense matrix from eigen
- result C can be either dense or sparse
---------------------------------------------------------*/

// C is a DENSE or SPARSE matrix
template <
  typename TA, typename TB, typename TC,
  core::meta::enable_if_t<
    core::meta::is_eigen_sparse_matrix_wrapper<TA>::value and
    core::meta::is_eigen_dense_matrix_wrapper<TB>::value and
    core::meta::wrapper_triplet_have_same_scalar<TA,TB,TC>::value and
    (core::meta::is_eigen_dense_matrix_wrapper<TC>::value or
     core::meta::is_eigen_sparse_matrix_wrapper<TC>::value )
    > * = nullptr
  >
void product(const TA & A, const TB & B, TC & C){
  assert(C.rows() == A.rows());
  assert(C.cols() == B.cols());
  (*C.data()) = (*A.data()) * (*B.data());
}


template <
  typename TA, typename TB,
  bool transposeA = false, bool transposeB = false,
  core::meta::enable_if_t<
    core::meta::is_eigen_sparse_matrix_wrapper<TA>::value and
    core::meta::is_eigen_dense_matrix_wrapper<TB>::value and
    core::meta::wrapper_pair_have_same_scalar<TA,TB>::value
    > * = nullptr
  >
TB product(const TA & A,
	     const TB & B){
  TB C(A.rows(),B.cols());
  product(A, B, C);
  return C;
}



}}} // end namespace rompp::core::ops
#endif
