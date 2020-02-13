#include <gtest/gtest.h>
#include <Tpetra_Map.hpp>
#include <Tpetra_Vector.hpp>
#include "CONTAINERS_ALL"

TEST(containers_vector_distributed_tpetra, Traits){
  using namespace pressio;

  using ST = double;
  using LO = int;
  using GO = unsigned long;
  typedef Tpetra::Vector<>::node_type NT;
  typedef Tpetra::Map<LO, GO, NT> map_type;
  
  using natV_t = Tpetra::Vector<ST, LO, GO, NT>;
  STATIC_ASSERT_IS_VECTOR_TPETRA(natV_t);
  STATIC_ASSERT_IS_NOT_VECTOR_EIGEN(natV_t);
  STATIC_ASSERT_IS_NOT_VECTOR_EPETRA(natV_t);

  using myvec_t = containers::Vector<natV_t>;
  STATIC_ASSERT_IS_NOT_VECTOR_EIGEN(myvec_t);
  STATIC_ASSERT_IS_NOT_VECTOR_EPETRA(myvec_t);

  using vecTrait = containers::details::traits<myvec_t>;
 
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::scalar_t, double>();
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::local_ordinal_t,int>();
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::global_ordinal_t,unsigned long>();
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::data_map_t, map_type>();
  
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::wrapped_t, natV_t>();
  ::testing::StaticAssertTypeEq<typename
				vecTrait::node_t, NT>();

  // using dev_ms_t = typename vecTrait::device_mem_space_t;
  // using dev_es_t = typename vecTrait::device_exec_space_t;
  // using host_ms_t = typename vecTrait::host_mem_space_t;
  // using host_es_t = typename vecTrait::host_exec_space_t;  
  // ::testing::StaticAssertTypeEq<host_ms_t, dev_ms_t>();
  // ::testing::StaticAssertTypeEq<host_es_t, dev_es_t>();
  
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::dot_t, double>();
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::mag_t, double>();  
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::derived_t, myvec_t>();
  ::testing::StaticAssertTypeEq<typename
  				vecTrait::communicator_t,
				Teuchos::RCP<const Teuchos::Comm<int>>
				>();
  
  ASSERT_TRUE(vecTrait::is_vector == true);
  ASSERT_TRUE(vecTrait::is_shared_mem == false);
  ASSERT_TRUE(vecTrait::is_dynamic == true);

  ASSERT_TRUE(vecTrait::wrapped_vector_identifier
	      == containers::details::WrappedVectorIdentifier::Tpetra);

    
}//end TEST
