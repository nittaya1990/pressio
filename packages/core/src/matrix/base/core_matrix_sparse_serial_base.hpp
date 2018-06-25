
#ifndef CORE_MATRIX_SPARSE_SERIAL_BASE_HPP_
#define CORE_MATRIX_SPARSE_SERIAL_BASE_HPP_

#include "../core_matrix_traits.hpp"

namespace core{
    
template<typename derived_type>
class matrixSparseSerialBase
{
private:
  using traits_t = details::traits<derived_type>;
  using der_t = typename traits_t::derived_t;
  using wrap_t = typename traits_t::wrapped_t;
  using ord_t = typename traits_t::ordinal_t;
  using sc_t = typename traits_t::scalar_t;
    
public:
  ord_t rows() const{
    return this->underlying().rowsImpl();
  }

  ord_t cols() const{
    return this->underlying().colsImpl();
  }

  void resize(ord_t nrows, ord_t ncols){
    return this->underlying().resizeImpl(nrows, ncols);
  }

  ord_t nonZerosCount()const{
    return this->underlying().nonZerosCountImpl();
  }
  
  //------------------------------------------------------------------
  // note this insert one by one might not be the best method
  // for efficiency. But it provides a simple nice way to store.
  //------------------------------------------------------------------
  void insertValues(ord_t targetLocation, ord_t numEntries,
		    const sc_t * values, const ord_t * indices){
    return this->underlying().insertValuesImpl(targetLocation, numEntries,
					       values, indices);
  }

  // note here that we return by copy. We do not enable to refernce []
  // because it makes little sense for a sparse matrix
  sc_t operator() (ord_t row, ord_t col) const;
  
private:  
  friend der_t;
  matrixSparseSerialBase() = default;
  ~matrixSparseSerialBase() = default;
 
private:  
  der_t & underlying(){
    return static_cast<der_t &>(*this);
  };
  der_t const& underlying() const{
    return static_cast<der_t const&>(*this);
  };


};//end class
} // end namespace core
#endif
