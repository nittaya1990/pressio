#ifndef SOLVERS_LINEAR_TAGS_HPP
#define SOLVERS_LINEAR_TAGS_HPP

namespace pressio{ namespace solvers{ namespace linear {

namespace iterative{
  struct CG {};
  struct LSCG {};
  struct Bicgstab {};
}//end iterative


namespace direct{
  struct ColPivHouseholderQR {};
  //struct CompleteOrthogonalDecomposition {};
}//end direct


// // Preconditioner types
// struct Jacobi {};
// struct DefaultPreconditioner {};

}}}//end namespace pressio::solvers::linear

#endif
