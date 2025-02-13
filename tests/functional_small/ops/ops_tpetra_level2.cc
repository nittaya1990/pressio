
#include "tpetra_only_fixtures.hpp"
#include "pressio/ops.hpp"

TEST_F(tpetraMultiVectorGlobSize15Fixture, mv_prod_kokkos_vector)
{
    auto myMv_h = myMv_->getLocalViewHost();
    for (int i=0; i<localSize_; ++i){
     for (int j=0; j<numVecs_; ++j){
        myMv_h(i,j) = (double)j;
     }
    }

    Kokkos::View<double*> a("a", numVecs_);
    KokkosBlas::fill(a, 1.);

    vec_t y(contigMap_);
    y.putScalar(0.);
    pressio::ops::product(::pressio::nontranspose{}, 1., *myMv_, a, 1., y);

    auto y_h = y.getLocalViewHost();
    EXPECT_DOUBLE_EQ(y_h(0,0), 6.);
    EXPECT_DOUBLE_EQ(y_h(1,0), 6.);
    EXPECT_DOUBLE_EQ(y_h(2,0), 6.);
    EXPECT_DOUBLE_EQ(y_h(3,0), 6.);
}

TEST_F(tpetraMultiVectorGlobSize15Fixture, mv_T_vector_storein_kokkos_vector)
{
    auto myMv_h = myMv_->getLocalViewHost();
    for (int i=0; i<localSize_; ++i){
     for (int j=0; j<numVecs_; ++j){
        myMv_h(i,j) = (double)i;
     }
    }

    vec_t y(contigMap_);
    y.putScalar(2.);

    Kokkos::View<double*> a("a", numVecs_);
    KokkosBlas::fill(a, 1.);
    pressio::ops::product(::pressio::transpose{}, 1., *myMv_, y, 1., a);

    auto a_h = Kokkos::create_mirror_view(a);
    Kokkos::deep_copy(a_h, a);
    EXPECT_DOUBLE_EQ(a(0), 61.);
    EXPECT_DOUBLE_EQ(a(1), 61.);
    EXPECT_DOUBLE_EQ(a(2), 61.);
    EXPECT_DOUBLE_EQ(a(3), 61.);
}

#ifdef PRESSIO_ENABLE_TPL_EIGEN
TEST_F(tpetraMultiVectorGlobSize15Fixture, mv_prod_eigen_vector)
{
    auto myMv_h = myMv_->getLocalViewHost();
    for (int i=0; i<localSize_; ++i){
     for (int j=0; j<numVecs_; ++j){
        myMv_h(i,j) = (double)j;
     }
    }

    Eigen::VectorXd a(numVecs_);
    a.setConstant(1.);

    vec_t y(contigMap_);
    y.putScalar(0.);
    pressio::ops::product(::pressio::nontranspose{}, 1., *myMv_, a, 1., y);

    auto y_h = y.getLocalViewHost();
    EXPECT_DOUBLE_EQ(y_h(0,0), 6.);
    EXPECT_DOUBLE_EQ(y_h(1,0), 6.);
    EXPECT_DOUBLE_EQ(y_h(2,0), 6.);
    EXPECT_DOUBLE_EQ(y_h(3,0), 6.);
}

TEST_F(tpetraMultiVectorGlobSize15Fixture, mv_T_vector_storein_eigen_vector)
{
    auto myMv_h = myMv_->getLocalViewHost();
    for (int i=0; i<localSize_; ++i){
     for (int j=0; j<numVecs_; ++j){
        myMv_h(i,j) = (double)i;
     }
    }

    vec_t y(contigMap_);
    y.putScalar(2.);

    Eigen::VectorXd a(numVecs_);
    a.setConstant(1.);
    pressio::ops::product(::pressio::transpose{}, 1., *myMv_, y, 1., a);

    EXPECT_DOUBLE_EQ(a(0), 61.);
    EXPECT_DOUBLE_EQ(a(1), 61.);
    EXPECT_DOUBLE_EQ(a(2), 61.);
    EXPECT_DOUBLE_EQ(a(3), 61.);
}
#endif
