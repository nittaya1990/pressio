
#ifndef PRESSIO_TESTS_WLS_BURGERS1D_FOM_FUNCTIONS_EIGEN_HPP_
#define PRESSIO_TESTS_WLS_BURGERS1D_FOM_FUNCTIONS_EIGEN_HPP_

#include "utils_eigen.hpp"

namespace pressio{ namespace testing{ namespace wls{

template <typename decoder_d_t>
decoder_d_t readBasis( pressio::apps::Burgers1dEigen & appObj,
		       ::pressio::ode::BDF1 odeTag,
		       std::size_t romSize,
		       std::size_t fomSize)
{
  const auto phi = pressio::rom::test::eigen::readBasis("basis_euler.txt", romSize, fomSize);
  decoder_d_t decoderObj(std::move(phi));
  return decoderObj;
}

template <typename decoder_d_t>
decoder_d_t readBasis(pressio::apps::Burgers1dEigen & appObj,
		      ::pressio::ode::BDF2 odeTag,
		      std::size_t romSize,
		      std::size_t fomSize)
{
  const auto phi = pressio::rom::test::eigen::readBasis("basis_bdf2.txt", romSize, fomSize);
  decoder_d_t decoderObj(std::move(phi));
  return decoderObj;
}

template<typename y1_t, typename y2_t, typename int_t>
std::string checkSol(pressio::apps::Burgers1dEigen & appObj,
		     const y1_t & yFinal,
		     const y2_t & trueY,
		     int_t fomSize)
{
  std::string checkStr {"PASSED"};
  for (int_t i=0;i<fomSize;i++){
    if (std::abs(yFinal(i) - trueY[i]) > 1e-10) checkStr = "FAILED";
  }
  return checkStr;
}



template <typename decoder_d_t>
decoder_d_t readBasis( pressio::apps::Burgers1dEigenDiscreteTimeApi & appObj,
		       ::pressio::ode::BDF1 odeTag,
		       std::size_t romSize,
		       std::size_t fomSize)
{
  const auto phi = pressio::rom::test::eigen::readBasis("basis_euler.txt", romSize, fomSize);
  decoder_d_t decoderObj(std::move(phi));
  return decoderObj;
}

template <typename decoder_d_t>
decoder_d_t readBasis(pressio::apps::Burgers1dEigenDiscreteTimeApi & appObj,
		      ::pressio::ode::BDF2 odeTag,
		      std::size_t romSize,
		      std::size_t fomSize)
{
  const auto phi = pressio::rom::test::eigen::readBasis("basis_bdf2.txt", romSize, fomSize);
  decoder_d_t decoderObj(std::move(phi));
  return decoderObj;
}

template<typename y1_t, typename y2_t, typename int_t>
std::string checkSol(pressio::apps::Burgers1dEigenDiscreteTimeApi & appObj,
		     const y1_t & yFinal,
		     const y2_t & trueY,
		     int_t fomSize)
{
  std::string checkStr {"PASSED"};
  for (int_t i=0;i<fomSize;i++){
    if ((std::abs(yFinal(i) - trueY[i]) > 1e-10) or std::isnan(yFinal(i))) checkStr = "FAILED";
  }
  return checkStr;
}


}}} //end namespace pressio::testing::wls
#endif
