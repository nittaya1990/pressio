
#ifndef CORE_MATRIX_OPERATIONS_DENSE_MATRIX_TRANSPOSE_HPP_
#define CORE_MATRIX_OPERATIONS_DENSE_MATRIX_TRANSPOSE_HPP_

#include "../../meta/core_matrix_meta.hpp"
#include "../concrete/core_matrix_dense_sharedmem_eigen.hpp"

namespace core{
namespace mat_ops{

/*-----------------------------------------------------
  EIGEN DENSE DYNAMIC
----------------------------------------------------- */
template <typename mat_type,
	  core::meta::enable_if_t<
	    details::traits<mat_type>::isEigen &&
	    details::traits<mat_type>::isDense &&
	    details::traits<mat_type>::isStatic==0
	    > * = nullptr>
auto transpose(const mat_type & A)
{
  mat_type res(A);
  res.data()->transposeInPlace();
  return res;
}

/*-----------------------------------------------------
  EIGEN DENSE STATIC
----------------------------------------------------- */
template <typename mat_type,
	  core::meta::enable_if_t<
	    details::traits<mat_type>::isEigen &&
	    details::traits<mat_type>::isDense &&
	    details::traits<mat_type>::isStatic
	    > * = nullptr>
auto transpose(const mat_type & A)
{
  using scalar_t = typename details::traits<mat_type>::scalar_t;
  static constexpr int rowsIn
    = details::traits<mat_type>::wrapped_t::RowsAtCompileTime;
  static constexpr int colsIn
    = details::traits<mat_type>::wrapped_t::ColsAtCompileTime;

  using res_t = core::Matrix<Eigen::Matrix<scalar_t, colsIn, rowsIn>>;
  res_t res;
  *res.data() = A.data()->transpose().eval();
  return res;
}
  

// /*-----------------------------------------------------
//   EPETRA DENSE MATRIX
// ----------------------------------------------------- */
// template <typename mat_type,
// 	  typename std::enable_if<
// 	    details::traits<mat_type>::isEpetra &&
// 	    details::traits<mat_type>::isDense
// 	    >::type * = nullptr>
// auto transpose(const mat_type & A) 
// {
//   // auto & mapA = A.getDataMap();
//   auto const & mpicomm = A.commCRef();
    
//   // let's ensure that the transposed matrix cna be distributed
//   // over the current processes, so the nuber of of cols of A
//   // needs to be greater than the number of MPI processes running 
//   const int numProc = mpicomm.NumProc();
//   if( numProc > A.globalCols() ){
//     std::cout << " ERROR: trying to transpose a dense dist matrix \
// with number of columns too small to be distributed over current communicator \n";}
//   assert( numProc < A.globalRows() );

//   Epetra_Map mapT(A.globalCols(), 0, mpicomm);  
//   mat_type C( mapT, A.globalRows() );
//   C.setZero();

//   // missing impl
  
//   return C;
// }
  
  
} // end namespace mat_ops
} // end namespace core
#endif
