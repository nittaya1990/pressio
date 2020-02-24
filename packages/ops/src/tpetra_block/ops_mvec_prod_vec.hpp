/*
//@HEADER
// ************************************************************************
//
// ops_mvec_prod_vec.hpp
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

#ifdef PRESSIO_ENABLE_TPL_TRILINOS
#ifndef OPS_SRC_OPS_TPETRA_BLOCK_MULTI_VECTOR_PROD_VECTOR_HPP_
#define OPS_SRC_OPS_TPETRA_BLOCK_MULTI_VECTOR_PROD_VECTOR_HPP_

namespace pressio{ namespace ops{

/*
 * multi_vector prod vector
 *
 * y = beta * y + alpha*op(A)*x
 *
*/

/* -------------------------------------------------------------------
 * op(A) = A
 * x is a sharedmem vector kokkos wrapper
 *-------------------------------------------------------------------*/
template < typename A_type, typename x_type, typename scalar_type, typename y_type>
::pressio::mpl::enable_if_t<
  containers::meta::is_multi_vector_wrapper_tpetra_block<A_type>::value and
  containers::meta::is_vector_wrapper_kokkos<x_type>::value and
  containers::meta::is_vector_wrapper_tpetra_block<y_type>::value
  >
product(::pressio::nontranspose mode,
	const scalar_type alpha,
	const A_type & A,
	const x_type & x,
	const scalar_type beta,
	y_type & y)
{
  throw std::runtime_error("Error, y = beta*y + alpha*A*x for tpetra block not yet supported");

  // static_assert(containers::meta::are_scalar_compatible<A_type, x_type, y_type>::value,
  //   "Types are not scalar compatible");

  // // make sure the tpetra mv has same exe space of the kokkos vector wrapper
  // using tpetra_mv_dev_t = typename ::pressio::containers::details::traits<A_type>::device_t;
  // using kokkos_v_dev_t  = typename ::pressio::containers::details::traits<x_type>::device_type;
  // static_assert( std::is_same<tpetra_mv_dev_t, kokkos_v_dev_t>::value,
  // 		 "product: tpetra MV and kokkos wrapper need to have same device type" );

  // assert( A.globalNumVectors() == x.size() );
  // const char ctA = 'N';

  // // the the underlying tpetra multivector
  // const auto mvView = A.data()->getMultiVectorView();
  // // get a local view
  // const auto ALocalView_d = mvView.getLocalViewDevice();
  // // I need to do the following because Tpetra::Vector is implemented
  // // as a special case of MultiVector so getLocalView returns a rank-2 view
  // // so in order to get view with rank==1 I need to explicitly get the subview
  // const auto yView = y.data()->getVectorView();
  // const auto yLocalView_drank2 = yView.getLocalViewDevice();
  // const auto yLocalView_drank1 = Kokkos::subview(yLocalView_drank2, Kokkos::ALL(), 0);
  // KokkosBlas::gemv(&ctA, alpha, ALocalView_d, *x.data(), beta, yLocalView_drank1);
}


/* -------------------------------------------------------------------
 * op(A) = A
 * x is a sharedmem vector but NOT kokkos
 *-------------------------------------------------------------------*/
template < typename A_type, typename x_type, typename scalar_type, typename y_type>
::pressio::mpl::enable_if_t<
  containers::meta::is_multi_vector_wrapper_tpetra_block<A_type>::value and
  !containers::meta::is_vector_wrapper_kokkos<x_type>::value and
  containers::meta::is_vector_wrapper_tpetra_block<y_type>::value
  >
product(::pressio::nontranspose mode,
	const scalar_type alpha,
	const A_type & A,
	const ::pressio::containers::VectorSharedMemBase<x_type> & x,
	const scalar_type beta,
	y_type & y)
{
  throw std::runtime_error("Error, y = beta*y + alpha*A*x for tpetra block not yet supported");

  // static_assert(containers::meta::are_scalar_compatible<A_type, x_type, y_type>::value,
  //   "Types are not scalar compatible");

  // const auto numVecs = A.globalNumVectors();
  // assert(size_t(numVecs) ==  x.extent(0));

  // // get the wrapped trilinos tpetra multivector
  // const auto A_mvv = A.data()->getMultiVectorView();
  // const auto A_hv = A_mvv.template getLocalView<Kokkos::HostSpace>();
  // // my number of rows
  // const auto myNrows = A_mvv.getLocalLength();

  // // the result is a block tpetra vector, get the regular tpetra vector
  // auto y_vv = y.data()->getVectorView();
  // auto y_hv = y_vv.template getLocalView<Kokkos::HostSpace>();
  // y_vv.template modify<Kokkos::HostSpace>();

  // for (std::size_t i=0; i<(std::size_t)myNrows; i++){
  //   for (std::size_t j=0; j<(std::size_t)numVecs; j++){
  //     // we use y_hv(i,0) because C is Tpetra::Vector, which is
  //     // actually a Tpetra::MultiVector with one column, so y_hv
  //     // is a kokkos::View<scalar**,...> so we need to index the zero column
  //     y_hv(i,0) = beta * y_hv(i,0) + alpha * A_hv(i,j) * x[j];
  //   }
  // }
  // using device_t = typename ::pressio::containers::details::traits<res_type>::device_t;
  // y.data()->template sync<device_t>();
}


/* -------------------------------------------------------------------
 * op(A) = A^T
 * x is a sharedmem vector wrapper not kokkos
 *-------------------------------------------------------------------*/
template <typename A_type, typename x_type, typename y_type, typename scalar_type>
::pressio::mpl::enable_if_t<
  containers::meta::is_multi_vector_wrapper_tpetra_block<A_type>::value and
  containers::meta::is_vector_wrapper_tpetra_block<x_type>::value and
  !containers::meta::is_vector_wrapper_kokkos<y_type>::value
  >
product(::pressio::transpose mode,
	const scalar_type alpha,
	const A_type & A,
	const x_type & x,
	const scalar_type beta,
	::pressio::containers::VectorSharedMemBase<y_type> & y)
{
  throw std::runtime_error("Error, y = beta*y + alpha*A^T*x for tpetra block not yet supported");

  // /* workaround the non-constness of getVectorView*/
  // using tpetra_blockvec_t = typename containers::details::traits<vec_type>::wrapped_t;
  // const auto vecB_vv = const_cast<tpetra_blockvec_t*>(vecB.data())->getVectorView();
  // const auto mvA_mvv = mvA.data()->getMultiVectorView();
  // const auto numVecs = mvA.globalNumVectors();
  // for (std::size_t i=0; i<(std::size_t)numVecs; i++){
  //   // colI is a Teuchos::RCP<Vector<...>>
  //   const auto colI = mvA_mvv.getVector(i);
  //   result[i] = colI->dot(vecB_vv);
  // }
}

/* -------------------------------------------------------------------
 * op(A) = A^T
 * x is a sharedmem vector kokkos wrapper
 *-------------------------------------------------------------------*/
template <typename A_type, typename x_type, typename y_type, typename scalar_type>
::pressio::mpl::enable_if_t<
  containers::meta::is_multi_vector_wrapper_tpetra_block<A_type>::value and
  containers::meta::is_vector_wrapper_tpetra_block<x_type>::value and
  containers::meta::is_vector_wrapper_kokkos<y_type>::value
  >
product(::pressio::transpose mode,
	const scalar_type alpha,
	const A_type & A,
	const x_type & x,
	const scalar_type beta,
	y_type & y)
{
  throw std::runtime_error("Error, y = beta*y + alpha*A^T*x for tpetra block not yet supported");

  // const auto mvA_mvv = mvA.data()->getMultiVectorView();
  // using tpetra_blockvector_t = typename containers::details::traits<vec_type>::wrapped_t;
  // const auto vecB_vv = const_cast<tpetra_blockvector_t*>(vecB.data())->getVectorView();
  // auto request = Tpetra::idot( *result.data(), mvA_mvv, vecB_vv);
  // request->wait();
}

}}//end namespace pressio::ops
#endif
#endif
