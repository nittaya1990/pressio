
#ifndef CORE_MATRIX_BASE_MATRIX_SPARSE_SERIAL_BASE_HPP_
#define CORE_MATRIX_BASE_MATRIX_SPARSE_SERIAL_BASE_HPP_

#include "../core_matrix_traits.hpp"

namespace core{
    
template<typename derived_type>
class MatrixSparseSerialBase
  : private core::details::CrtpBase<
  MatrixSparseSerialBase<derived_type>>
{

  static_assert( details::traits<derived_type>::isDistributed==0 &&
		 details::traits<derived_type>::isSerial==1,
		 "OOPS: distributed matrix inheriting \
from sparse serial base!");

private:
  using traits_t = details::traits<derived_type>;
  using ord_t = typename traits_t::ordinal_t;
  using sc_t = typename traits_t::scalar_t;    

public:
  ord_t nonZerosCount()const{
    return this->underlying().nonZerosCountImpl();
  }  

  void setIdentity(){
    this->underlying().setIdentityImpl();
  }
  
  //------------------------------------------------------------------
  // note this insert one by one might not be the best method
  // for efficiency. But it provides a simple nice way to store.
  // NOTE: targetLocation can be either a row index or a columnm
  // depending on whether the matrix is stored row-wise of columnwise.
  //------------------------------------------------------------------
  void insertValues(ord_t targetLocation,
		    ord_t numEntries,
		    const sc_t * values,
		    const ord_t * indices){
    this->underlying().insertValuesImpl(targetLocation,
					numEntries,
					values,
					indices);
  }
  
  // note here that we return by copy. We do not enable to refernce []
  // because it makes little sense for a sparse matrix
  sc_t operator() (ord_t row, ord_t col) const;
  
private:  
  friend derived_type;
  friend core::details::CrtpBase<
    MatrixSparseSerialBase<derived_type>>;

  MatrixSparseSerialBase() = default;
  ~MatrixSparseSerialBase() = default; 

};//end class
  
} // end namespace core
#endif
