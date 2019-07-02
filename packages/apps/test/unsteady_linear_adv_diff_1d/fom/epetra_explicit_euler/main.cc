
#include "CONTAINERS_ALL"
#include "ODE_EXPLICIT"
#include "APPS_UNSTEADYLINADVDIFF1D"
#include "../gold_states_explicit.hpp"

constexpr double eps = 1e-12;
std::string checkStr = "PASSED";

template <typename T>
void checkSol(int rank, const T & y,
	      const std::vector<double> & trueS){
  int shift = (rank==0) ? 0 : 5;
  for (auto i=0; i< y.localSize(); i++){
    if (std::abs(y[i] - trueS[i+shift]) > eps) checkStr = "FAILED";
  }
}

int main(int argc, char *argv[]){
  using app_t          =pressio::apps::UnsteadyLinAdvDiff1dEpetra;
  using scalar_t       =typename app_t::scalar_type;
  using app_state_t    =typename app_t::state_type;
  using app_rhs_t =typename app_t::velocity_type;
  using native_state   =typename app_t:: state_type;

  //----------------------------------------------------------------------
  // Initialize MPI
  //----------------------------------------------------------------------
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  Epetra_MpiComm Comm(MPI_COMM_WORLD);
  assert(Comm.NumProc() == 2);

  //----------------------------------------------------------------------
  // Parameters
  //----------------------------------------------------------------------
  const std::vector<scalar_t> mu{-1 , 1, 1};
  const std::vector<scalar_t> domain{0, 2.0, 0.2};
  const std::vector<scalar_t> bc1D{0, 0};

  //----------------------------------------------------------------------
  // Problem setup
  //----------------------------------------------------------------------
  app_t appObj(Comm, mu, domain, bc1D);
  appObj.unsteadySetup();
  const native_state y0n(*appObj.getInitialState());

  //----------------------------------------------------------------------
  // Rompp time integrator
  //----------------------------------------------------------------------
  using ode_state_t = pressio::containers::Vector<app_state_t>;
  using ode_res_t  = pressio::containers::Vector<app_rhs_t>;
  ode_state_t y(y0n);
  y.data()->Print(std::cout <<std::setprecision(14));

  constexpr auto ode_case = pressio::ode::ExplicitEnum::Euler;
  using stepper_t = pressio::ode::ExplicitStepper<
    ode_case, ode_state_t, app_t, ode_res_t, scalar_t>;
  stepper_t stepperObj(y, appObj);

  //Integrate in time
  scalar_t dt = 0.01;
  auto Nsteps = 100;//static_cast<unsigned int>(fint/dt);
  scalar_t fint = Nsteps*dt;
  pressio::ode::integrateNSteps(stepperObj, y, 0.0, dt, Nsteps);

  //----------------------------------------------------------------------
  // Results
  //----------------------------------------------------------------------
  y.data()->Print(std::cout <<std::setprecision(14));
  {
    using namespace pressio::apps::test;
    checkSol(rank, y,
	     UnsteadyLinAdvDiff1dExpGoldStates<ode_case>
	     ::get(mu, domain, bc1D, dt, fint));
  }

  MPI_Finalize();
  std::cout << checkStr << std::endl;
  return 0;
}
