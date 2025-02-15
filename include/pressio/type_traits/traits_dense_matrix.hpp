/*
//@HEADER
// ************************************************************************
//
// traits_dense_matrix.hpp
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

#ifndef TYPE_TRAITS_TRAITS_DENSE_MATRIX_HPP_
#define TYPE_TRAITS_TRAITS_DENSE_MATRIX_HPP_

namespace pressio{

#ifdef PRESSIO_ENABLE_TPL_EIGEN
//***********************************
// eigen dense matrix
//***********************************
template <typename T>
struct Traits<
  T,
  mpl::enable_if_t<
    is_dense_matrix_eigen<T>::value
    >
  >
  : public ContainersSharedTraits<PackageIdentifier::Eigen, true, 2>,
    public MatrixSharedTraits<false>
{

  static constexpr MatrixIdentifier matrix_identifier = MatrixIdentifier::DenseEigen;
  static constexpr bool is_static = ( T::RowsAtCompileTime != Eigen::Dynamic &&
                                      T::ColsAtCompileTime != Eigen::Dynamic );
  static constexpr bool is_dynamic  = !is_static;

  using scalar_type  = typename T::Scalar;
  using ordinal_type = typename T::StorageIndex;
  using size_type = ordinal_type;
  using reference_type = scalar_type &;
  using const_reference_type = scalar_type const &;
};
#endif //PRESSIO_ENABLE_TPL_EIGEN

//*******************************
// Kokkos dense matrix
//*******************************
#ifdef PRESSIO_ENABLE_TPL_KOKKOS
template <typename T>
struct Traits<
  T,
    ::pressio::mpl::enable_if_t<
      is_dense_matrix_kokkos<T>::value
    >
  >
  : public ContainersSharedTraits<PackageIdentifier::Kokkos, true, 2>,
  public MatrixSharedTraits<false>
{

  static constexpr MatrixIdentifier matrix_identifier = MatrixIdentifier::DenseKokkos;
  static constexpr bool is_static = T::traits::rank_dynamic==0;
  static constexpr bool is_dynamic  = !is_static;

  using scalar_type   = typename T::traits::value_type;
  using layout_type   = typename T::traits::array_layout;
  using ordinal_type  = typename T::traits::size_type;
  using size_type = ordinal_type;

  using execution_space   = typename T::traits::execution_space;
  using memory_space    = typename T::traits::memory_space;
  using device_type   = typename T::traits::device_type;
  using memory_traits   = typename T::traits::memory_traits;
  using host_mirror_space = typename T::traits::host_mirror_space;
  using host_mirror_t     = typename T::host_mirror_type;

  using reference_type = typename T::reference_type;

  static constexpr bool has_host_execution_space =
    (false
     #ifdef KOKKOS_ENABLE_SERIAL
     || std::is_same<execution_space, Kokkos::Serial>::value
     #endif
     #ifdef KOKKOS_ENABLE_OPENMP
     || std::is_same<execution_space, Kokkos::OpenMP>::value
     #endif
     );
};
#endif

//**********************************
// for teuchos serial dense matrix
//**********************************
#ifdef PRESSIO_ENABLE_TPL_TRILINOS
template<typename T>
struct Traits<
  T,
  mpl::enable_if_t<
    is_dense_matrix_teuchos<T>::value
    >
  >
  : public ContainersSharedTraits<PackageIdentifier::Trilinos, true, 2>,
    public MatrixSharedTraits<false>
{

  static constexpr MatrixIdentifier matrix_identifier = MatrixIdentifier::DenseTeuchosSerial;
  static constexpr bool is_static = false;
  static constexpr bool is_dynamic  = !is_static;

  using scalar_type = typename T::scalarType;
  using ordinal_type = typename T::ordinalType;
  using size_type = ordinal_type;
};
#endif

}
#endif  // TYPE_TRAITS_TRAITS_DENSE_MATRIX_HPP_
