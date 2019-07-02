
#ifdef HAVE_TRILINOS
#ifndef CONTAINERS_SHARED_BASE_CONTAINER_DISTRIBUTED_TRILINOS_BASE_HPP_
#define CONTAINERS_SHARED_BASE_CONTAINER_DISTRIBUTED_TRILINOS_BASE_HPP_

#include "../containers_ConfigDefs.hpp"
#include "Teuchos_RCPDecl.hpp"

namespace pressio{ namespace containers{

template<typename derived_type, typename map_t>
class ContainerDistributedTrilinosBase
  : private utils::details::CrtpBase<
  ContainerDistributedTrilinosBase<derived_type, map_t> >{

  using this_t = ContainerDistributedTrilinosBase<derived_type,map_t>;

public:
  map_t const & getDataMap() const{
    return this->underlying().getDataMapImpl();
  }

  bool hasRowMapEqualTo(map_t const &othermap) const{
    return this->underlying().hasRowMapEqualToImpl(othermap);
  }

  Teuchos::RCP<const map_t> getRCPDataMap() const{
    return this->underlying().getRCPDataMapImpl();
  }

  void replaceDataMap(const map_t & mapObj){
    return this->underlying().replaceDataMapImpl(mapObj);
  }

private:
  /* workaround for nvcc issue with templates, see https://devtalk.nvidia.com/default/topic/1037721/nvcc-compilation-error-with-template-parameter-as-a-friend-within-a-namespace/ */
  template<typename DummyType> struct dummy{using type = DummyType;};
  friend typename dummy<derived_type>::type;

  friend utils::details::CrtpBase<this_t>;

  ContainerDistributedTrilinosBase() = default;
  ~ContainerDistributedTrilinosBase() = default;

};//end class

}}//end namespace pressio::containers
#endif
#endif
