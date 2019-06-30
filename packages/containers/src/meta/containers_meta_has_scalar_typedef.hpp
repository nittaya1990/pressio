
#ifndef CONTAINERS_META_HAS_SCALAR_TYPEDEF_HPP_
#define CONTAINERS_META_HAS_SCALAR_TYPEDEF_HPP_

#include <type_traits>

namespace rompp{ namespace containers{ namespace meta {

template <typename T, typename enable = void>
struct has_scalar_typedef : std::false_type{};

template <typename T>
struct has_scalar_typedef<
  T,
  mpl::enable_if_t<
    !std::is_void<
      typename T::scalar_type
      >::value
    >
  > : std::true_type{};

}}}//end namespace rompp::containers::meta
#endif
