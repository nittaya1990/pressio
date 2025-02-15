
#include "pressio_rom_lspg.hpp"
#include "pressio_apps.hpp"
#include "utils_eigen.hpp"

std::string checkStr {"PASSED"};

template <typename rom_state_t, typename native_state_t>
struct observer{
  std::ofstream myfile_;
  std::ofstream myRefFile_;
  observer(const native_state_t & y0)
  : myfile_("solution.bin",  std::ios::out | std::ios::binary), 
    myRefFile_("state_ref.bin",  std::ios::out | std::ios::binary)
  {
    for (int i =0; i < y0.size(); i++){
      myRefFile_.write(reinterpret_cast<const char*>(&y0(i)),sizeof(y0(i)));
    }
    myRefFile_.close();
  }

  void operator()(size_t step,
  		  double t,
  		  const rom_state_t & y){
    auto ydata = *y.data();
    for (int i=0;i<y.extent(0);i++){
      myfile_.write(reinterpret_cast<const char*>(&ydata(i)),sizeof(ydata(i)));
    }
    std::cout << "Time = " << t << std::endl; 
  }

  void closeFile(){
    myfile_.close();
  }
};


/*
  Regression test for shallow water equation ROM
*/

int main(int argc, char *argv[])
{
  pressio::log::initialize(pressio::logto::terminal);

  std::string checkStr {"PASSED"};

  using fom_t		= pressio::apps::swe2d;
  using scalar_t	= typename fom_t::scalar_type;

  // -------------------------------------------------------
  // create FOM object
  // -------------------------------------------------------
  constexpr int nx = 8;
  constexpr int ny = 8;
  scalar_t params[3];
  params[0] = 9.8;
  params[1] = 0.125;
  params[2] = 0.25;
  constexpr scalar_t Lx = 5;
  constexpr scalar_t Ly = 5;
  fom_t appObj(Lx,Ly,nx,ny,params);
  constexpr scalar_t et = 10.;
  constexpr scalar_t dt = 0.5;


  // -------------------------------------------------------
  // read basis
  // -------------------------------------------------------
  using decoder_jac_t	= pressio::containers::MultiVector<Eigen::MatrixXd>;
  constexpr int romSize = 20;
  decoder_jac_t phi = pressio::rom::test::eigen::readBasis("basis.txt", romSize, 3*nx*ny);
  const int numBasis = phi.numVectors();
  if( numBasis != romSize ) return 0;

  // -------------------------------------------------------
  // create decoder obj
  // -------------------------------------------------------
  using native_state_t  = typename fom_t::state_type;
  using fom_state_t  = pressio::containers::Vector<native_state_t>;
  using decoder_t = pressio::rom::LinearDecoder<decoder_jac_t, fom_state_t>;
  decoder_t decoderObj(phi);

  native_state_t yRef(appObj.getGaussianIC(params[1]));
  // -------------------------------------------------------
  // create ROM problem
  // -------------------------------------------------------
  using lspg_state_t = pressio::containers::Vector<Eigen::Matrix<scalar_t,-1,1>>;

  // define ROM state
  lspg_state_t yROM(romSize);
  // initialize to zero (reference state is IC)
  pressio::ops::fill(yROM, 0.0);

  // define LSPG type
  using ode_tag  = pressio::ode::CrankNicolson;
  auto lspgProblem = pressio::rom::lspg::createDefaultProblemUnsteady<ode_tag>(
    appObj, decoderObj, yROM, yRef);

  // linear solver
  using eig_dyn_mat  = Eigen::Matrix<scalar_t, -1, -1>;
  using hessian_t  = pressio::containers::DenseMatrix<eig_dyn_mat>;
  using solver_tag   = pressio::solvers::linear::iterative::LSCG;
  using linear_solver_t = pressio::solvers::linear::Solver<solver_tag, hessian_t>;
  linear_solver_t linSolverObj;

  // GaussNewton solver with normal equations
  auto solver = pressio::rom::lspg::create_gauss_newtonSolver(lspgProblem, yROM, linSolverObj);
  auto Nsteps = static_cast<::pressio::ode::step_type>(et/dt);
  solver.setTolerance(1e-13);
  solver.setMaxIterations(10);

  // define observer
  observer<lspg_state_t,native_state_t> Obs(yRef);
  // solve
  pressio::rom::lspg::solveNSequentialMinimizations(lspgProblem, yROM, 0.0, dt, Nsteps, Obs,solver);
  auto yFomFinal = lspgProblem.fomStateReconstructorCRef()(yROM);
  constexpr double solNormGold = 8.1221307554237;
  auto solNorm = (*yFomFinal.data()).norm();
  Obs.closeFile();
  if (std::abs(solNorm - solNormGold) > 1e-12){
    checkStr = "Failed";
  }
  std::cout << checkStr << std::endl;
  pressio::log::finalize();

  return 0;
}
