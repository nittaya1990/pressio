
#ifndef ODE_REF_APPS_FOR_TESTING_HPP_
#define ODE_REF_APPS_FOR_TESTING_HPP_

namespace pressio{ namespace ode{ namespace testing{

// //************************************************
// struct fakeAppForTraitsForExp
// {
//   using scalar_type = double;
//   using state_type = std::vector<double>;
//   using velocity_type = std::vector<double>;

//   void velocity(const state_type & y,
//     scalar_type t, velocity_type & R) const{
//   };
//   velocity_type createVelocity()const{
//     velocity_type R;
//     return R;
//   };
// };
// //************************************************
// //************************************************

struct refAppEigen
{
  using scalar_type = double;
  using state_type = Eigen::VectorXd;
  using velocity_type = state_type;

  void velocity(const state_type & y,
		            scalar_type t,
                velocity_type & rhs) const
  {
    auto sz = y.size();
    for (decltype(sz) i=0; i<sz; i++){
      rhs[i] = y[i];
    }
  };

  velocity_type createVelocity() const{
    return velocity_type(3);
  };
};
//************************************************
//************************************************

struct refAppForImpEigen
{

  /*
    dy
    -- = -10*y
    dt

    y(0) = 1;
    y(1) = 2;
    y(2) = 3;

    for a given time-step, dt, we have:
       Euler backward yields:
          y_n = y_n-1/(1+10*dt)

       BDF2 yields:
          num = (4/3) * y_n-1 - (1/3) * y_n-2
	  den = 1 + (20/3) * dt
          y_n = num/den
   */
  using scalar_type = double;
  using state_type    = Eigen::VectorXd;
  using velocity_type = state_type;
  using jacobian_type = Eigen::SparseMatrix<double>;

  state_type y0_;
  state_type y;
  state_type y_nm1;
  state_type y_nm2;

public:
  refAppForImpEigen(){
    y.resize(3);
    y << 1., 2., 3.;
    y0_ = y;
  }

  state_type getInitCond() const{
    return y0_;
  }

  void velocity(const state_type & yIn,
    scalar_type t, velocity_type & R) const{
    assert(yIn.size()==3);
    R = -10. * yIn;
  };
  //--------------------------------------------

  velocity_type createVelocity() const
  {
    velocity_type R(3);
    return R;
  };
  //--------------------------------------------

  void jacobian(const state_type & yIn,
  		scalar_type t, jacobian_type & JJ) const{
    assert( JJ.rows() == 3 ); assert( JJ.cols() == 3 );

    typedef Eigen::Triplet<scalar_type> Tr;
    std::vector<Tr> tripletList;
    tripletList.push_back( Tr( 0, 0, -10.) );
    tripletList.push_back( Tr( 1, 1, -10.) );
    tripletList.push_back( Tr( 2, 2, -10.) );
    JJ.setFromTriplets(tripletList.begin(), tripletList.end());
  };
  //--------------------------------------------

  jacobian_type createJacobian() const
  {
    jacobian_type JJ(3,3);
    return JJ;
  };
  //--------------------------------------------

  void analyticAdvanceBackEulerNSteps(double dt, int n){
    double den = 1.0 + 10.*dt;
    for (int i=1; i!=n+1; i++)
    {
      y_nm1 = y;
      y[0] = y_nm1[0]/den;
      y[1] = y_nm1[1]/den;
      y[2] = y_nm1[2]/den;
    }
  };
  //--------------------------------------------

  void analyticAdvanceBDF2NSteps(double dt, int n){
    // here we assume that y_nm1 and y_nm2 are valid,
    // e.g. advanceBackEuler has already been called

    double den = 1.0 + (20./3.)*dt;
    for (int i=1; i!=n+1; i++)
    {
      y_nm2 = y_nm1;
      y_nm1 = y;
      double num1 = (4./3.) * y_nm1[0] - (1./3.) * y_nm2[0];
      double num2 = (4./3.) * y_nm1[1] - (1./3.) * y_nm2[1];
      double num3 = (4./3.) * y_nm1[2] - (1./3.) * y_nm2[2];

      y[0] = num1/den;
      y[1] = num2/den;
      y[2] = num3/den;
    }
  };

  void analyticAdvanceRK4(double dt)
  {
    assert(dt==0.1);
    velocity_type k1(3), k2(3), k3(3), k4(3);
    //I did the math...
    k1 << -1., -2, -3.;
    k2 << -0.5, -1, -1.5;
    k3 << -0.75, -1.5, -2.25;
    k4 << -0.25, -0.5, -0.75;
    y += (1./6.) * (k1 + 2.*k2 + 2.*k3 + k4);
  };
  //--------------------------------------------

};//end app refAppForImpEigen
//************************************************
//************************************************



struct refAppForArbitraryImpl
{
  using scalar_type   = double;
  using state_type    = Eigen::VectorXd;
  using residual_type = state_type;
  using jacobian_type = Eigen::SparseMatrix<double>;

public:

  template <typename step_t, typename ... Args>
  void timeDiscreteResidual(const step_t & step,
                            const scalar_type & time,
                            const scalar_type & dt,
                            residual_type &,
                            Args & ... states) const
  {
    //timeDiscreteResidualImpl<step_t>( step, time, f, std::forward<Args>(states)... );
  }

  residual_type createTimeDiscreteResidual() const
  {
    // initialize which depends on the app and data structure types used
    residual_type R(3);
    // this->timeDiscreteResidual(step, time, g, std::forward<Args>(states)...);
    return R;
  }

  template <typename step_t, typename ... Args>
  void timeDiscreteJacobian(const step_t & step,
                            const scalar_type & time,
                            const scalar_type & dt,
                            jacobian_type &,
                            Args & ... states) const
  {
    // forward to whatever approriate impl method, e. g.
    // timeDiscreteJacobianImpl<step_t>( step, time, f, std::forward<Args>(states)... );
  }

  jacobian_type createTimeDiscreteJacobian() const
  {
    // initialize which depends on the app and data structure types used
    jacobian_type J(3,3);
    // this->timeDiscreteJacobian(step, time, g, std::forward<Args>(states)...);
    return J;
  }

};//

}}} // namespace pressio::ode::testing
#endif
