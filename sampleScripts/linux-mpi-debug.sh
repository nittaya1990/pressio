#
# Set TRIBITS_DIR in the env then call this!
#

EXTRA_ARGS=$@
cmake \
-DTribitsExProj_TRIBITS_DIR=$TRIBITS_DIR \
-DTPL_ENABLE_MPI=ON \
-DTribitsExProj_ENABLE_Fortran=OFF \
-DTribitsExProj_ENABLE_TESTS=ON \
$EXTRA_ARGS \
/Users/fnrizzi/Desktop/test/pack
