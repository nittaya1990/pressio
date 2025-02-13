
#include "pressio_rom_lspg.hpp"

class Preconditioner
{
  using scalar_type = double;
  using state_type  = Eigen::VectorXd;
  using velocity_type = state_type;
  using dense_matrix_type = Eigen::MatrixXd;

public:
  void applyPreconditioner(const state_type & yState,
			   scalar_type time,
			   velocity_type & operand) const
  {
    for (auto i=0; i<operand.size(); ++i) operand(i)+=1.;
  }

  void applyPreconditioner(const state_type & yState,
			   scalar_type time,
			   dense_matrix_type & operand) const
  {
    assert(operand.cols()==3);
    for (auto i=0; i<operand.rows(); ++i)
      for (auto j=0; j<operand.cols(); ++j)
	operand(i,j) += static_cast<scalar_type>(1);
  }
};

struct MyFakeApp
{
  int Nst_ = {};
  int Nsm_ = {};
  int Nrom_ = {};

public:
  using scalar_type = double;
  using state_type  = Eigen::VectorXd;
  using velocity_type = state_type;
  using dense_matrix_type = Eigen::MatrixXd;

public:
  MyFakeApp(int Nst, int Nsm, int Nrom)
    : Nst_(Nst), Nsm_(Nsm), Nrom_(Nrom){}

  velocity_type createVelocity() const{
    state_type v(Nsm_); v.setZero();
    return v;
  }

  dense_matrix_type createApplyJacobianResult(const dense_matrix_type & B) const{
    dense_matrix_type A(Nsm_, B.cols()); A.setZero();
    return A;
  }

  void velocity(const state_type & state,
		const double & time,
		velocity_type & f) const
  {
    f(0) = 1.1;
    f(1) = 2.2;
    f(2) = 3.3;
    f(3) = 4.4;
    f(4) = 5.5;
  }

  void applyJacobian(const state_type &,
  		     const dense_matrix_type & B,
  		     scalar_type time,
  		     dense_matrix_type & A) const
  {
    for (auto j=0; j<A.cols(); ++j) A(0,j) = 2.0;
    for (auto j=0; j<A.cols(); ++j) A(1,j) = 3.0;
    for (auto j=0; j<A.cols(); ++j) A(2,j) = 4.0;
    for (auto j=0; j<A.cols(); ++j) A(3,j) = 5.0;
    for (auto j=0; j<A.cols(); ++j) A(4,j) = 6.0;
  }
};

struct MyLinearSolver
{
  using matrix_type = pressio::containers::DenseMatrix<Eigen::MatrixXd>;
  using vec_t       = pressio::containers::Vector<Eigen::VectorXd>;

  std::string & sentinel_;
  int count_ = 0;

  MyLinearSolver(std::string & sentinel) : sentinel_(sentinel){}

  void solve(const matrix_type & A, const vec_t & b, vec_t & x)
  {
    count_++;
    pressio::ops::fill(x, 1.);
    std::cout << "A" << std::endl;
    std::cout << *A.data() << std::endl;
    std::cout << "b" << std::endl;
    std::cout << *b.data() << std::endl;

    if (count_ == 1)
    {
      Eigen::VectorXd bGold(3); bGold.setConstant(-7.24);
      if (!bGold.isApprox(*b.data())) sentinel_ = "FAILED";

      Eigen::MatrixXd hGold(3,3); hGold.setConstant(215.8);
      if (!hGold.isApprox(*A.data())) sentinel_ = "FAILED";
    }

    if (count_ == 2)
    {
      Eigen::VectorXd bGold(3); bGold.setConstant(-645.04);
      if (!bGold.isApprox(*b.data())) sentinel_ = "FAILED";

      Eigen::MatrixXd hGold(3,3); hGold.setConstant(215.8);
      if (!hGold.isApprox(*A.data())) sentinel_ = "FAILED";
    }
  }
};

int main(int argc, char *argv[])
{
  /*
  check that the preconditioned hyp-red lspg problem works as expected.
  We don't solve a real problem but we we use fake data and veryify that
  at every stage involved, from constructor to fom querying to solve,
  the data is supposed to be correct.
  We have the following:
  - stencils mesh: 10 points enumerated as {0,1,...,9}
        o  o  o  o  o  o  o  o  o  o  (points)
        0  1  2  3  4  5  6  7  8  9  (indices of sample mesh points)

  - sample mesh: subset of stencils mesh points {1,4,5,7,8}
        *        *  *     *  *
        0        4  5     7  8  (indices wrt stencil mesh)
        0        1  2     3  4  (enumaration wrt to sample mesh only)

  - romSize = 3
  - start from romState = [0,0,0]
  - use GN with normal equations and do two iterations of the GN solver,
    inner linear solve: simply sets correction to be [1 1 ... 1]
  - linear mapping such that:
              phi = [ 1 1 1;
                      ...  ;
                     10 10 10]

  - we do one time steps: t0 -> t1, with dt = 0.2
  - the fomObj returns the velocity at the sample mesh points:
          f = [1.1 2.2 3.3 4.4 5.5]
  - the fomObj returns the applyJac which has size (Nsmesh, romSize)
    applyJac = [2 2 2;
                3 3 3;
                4 4 4;
                5 5 5;
                6 6 6]
  - the prec adds 1 to each entry of the given operand to act on

  =========================
  =========================
        time step 1
  =========================
  =========================

  *************************************
  *** first call to solver we have ***
  *************************************
  romState     = [0 0 0],
  fomState_n   = [0 ... 0]
  fomState_n-1 = [0 ... 0]

  R = applyPrec to (y_n - y_nm-1 - dt*f)
    = applyPrec to [-0.22 -0.44 -0.66 -0.88 -1.1]
    = [1-0.22 1-0.44 1-0.66 1-0.88 1-1.1]
    = [0.78 0.56 0.34 0.12 -0.1]

  lspgJac = applyPrec to (I*phi - dt*df/dy*phi)
  where I*phi is only taken at the sample mesh points
  and df/dy*phi = [2 2 2;
                   3 3 3;
                   4 4 4;
                   5 5 5;
                   6 6 6]
  we get:
  lspgJac before prec = [2-dt*2 2-dt*2 2-dt*2;    [1.6 1.6 1.6;
			 5-dt*3 5-dt*3 5-dt*3;     4.4 4.4 4.4;
			 6-dt*4 6-dt*4 6-dt*4; =   5.2 5.2 5.2;
			 8-dt*5 8-dt*5 8-dt*5;     7.0 7.0 7.0;
			 9-dt*6 9-dt*6 9-dt*6]     7.8 7.8 7.8]
  lspgJac = lspgJac += 1
          = [2.6 2.6 2.6
	     5.4 5.4 5.4
	     6.2 6.2 6.2
	     8.0 8.0 8.0
	     8.8 8.8 8.8]

  so that the first call to the linear solver should have:
  b = -lspgJac^T R = [ -7.24 -7.24 -7.24]
  neg sign because of the sign convention in pressio

  A = (lspgJac)^T (lspgJac) =
        [215.8 215.8 215.8;
         215.8 215.8 215.8;
         215.8 215.8 215.8]


  *************************************
  *** second call to solver we have ***
  *************************************
  romState     = [1 1 1],
  fomState_n   = [3 6 9 12 15 18 21 24 27 30]
  fomState_n-1 = [0 ... 0]

  R = applyPrc to (y_n - y_nm-1 - dt*f)
    = applyPrec to [6-0.22 15-0.44 18-0.66 24-0.88 27-1.1]
    = applyPrec to [5.78 14.56 17.34 23.12 25.9]
    = [6.78 15.56 18.34 24.12 26.9]

  lspgJac = applyPrec to (I*phi - dt*df/dy*phi)
  where I*phi is only taken at the sample mesh points
  and df/dy*phi = [2 2 2;
                   3 3 3;
                   4 4 4;
                   5 5 5;
                   6 6 6]
  we get:
  lspgJac befor prec = [2-dt*2 2-dt*2 2-dt*2;    [1.6 1.6 1.6;
			5-dt*3 5-dt*3 5-dt*3;     4.4 4.4 4.4;
			6-dt*4 6-dt*4 6-dt*4; =   5.2 5.2 5.2;
			8-dt*5 8-dt*5 8-dt*5;     7.0 7.0 7.0;
			9-dt*6 9-dt*6 9-dt*6]     7.8 7.8 7.8]
  lspgJac = lspgJac += 1
          = [2.6 2.6 2.6
	     5.4 5.4 5.4
	     6.2 6.2 6.2
	     8.0 8.0 8.0
	     8.8 8.8 8.8]

  so that the first call to the linear solver should have:
  b = -lspgJac^T R = [ -645.04 -645.04 -645.04 ]
  the neg sign because of the sign convention in pressio

  A = (lspgJac)^T (lspgJac) =
  [215.8 215.8 215.8;
   215.8 215.8 215.8;
   215.8 215.8 215.8]
  */

  std::string checkStr {"PASSED"};

  using fom_t		= MyFakeApp;
  using native_state_t  = typename fom_t::state_type;
  using fom_state_t	= pressio::containers::Vector<native_state_t>;
  using rom_state_t	= pressio::containers::Vector<Eigen::VectorXd>;

  constexpr int Nstencil = 10;
  constexpr int Nsmesh   = 5;
  constexpr int romSize  = 3;

  // app object
  fom_t appObj(Nstencil, Nsmesh, romSize);

  // decoder
  using native_dmatrix_t = typename fom_t::dense_matrix_type;
  using decoder_jac_t	 = pressio::containers::MultiVector<native_dmatrix_t>;
  using decoder_t	 = pressio::rom::LinearDecoder<decoder_jac_t, fom_state_t>;
  decoder_jac_t phi(Nstencil, romSize);
  for (auto i=0; i<Nstencil; ++i)
    for (auto j=0; j<romSize; ++j)
      phi(i,j) = (double) (i+1);

  decoder_t  decoderObj(phi);

  // this is my reference state
  native_state_t refState(Nstencil);
  refState.setConstant(1.0);

  // define ROM state
  rom_state_t romState(romSize);
  pressio::ops::fill(romState, 0.0);

  pressio::containers::Vector<Eigen::Matrix<int,-1,1>> hrIndices(Nsmesh);
  hrIndices(0) = 1;
  hrIndices(1) = 4;
  hrIndices(2) = 5;
  hrIndices(3) = 7;
  hrIndices(4) = 8;

  // prec obj
  Preconditioner precObj;

  using odetag = pressio::ode::BDF1;
  auto problem = pressio::rom::lspg::createPreconditionedHyperReducedProblemUnsteady<odetag>
    (appObj, decoderObj, romState, refState, precObj, hrIndices);

  MyLinearSolver linSolverObj(checkStr);

  // GaussNewton solver with normal equations
  auto solver = pressio::rom::lspg::create_gauss_newtonSolver(problem, romState, linSolverObj);
  solver.setMaxIterations(2);
  solver.setStoppingCriterion(pressio::solvers::nonlinear::Stop::AfterMaxIters);

  pressio::rom::lspg::solveNSequentialMinimizations(problem,romState, 0.0, 0.2, 1, solver);

  std::cout << checkStr <<  std::endl;
  return 0;
}
