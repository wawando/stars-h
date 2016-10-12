#include <stdio.h>
#include <stdlib.h>
#include "stars.h"
#include "stars-spatial.h"

int main(int argc, char **argv)
    // Example of how to use STARS library for spatial statistics.
    // For more information on STARS structures look inside of header files.
{
    int block_size = 50, block_count = 100;
    double beta = 0.1, tol = 1e-3;
    STARS_Problem *problem;
    STARS_BLR *format;
    STARS_BLRmatrix *matrix;
    format = STARS_gen_ss_blrformat(block_size, block_count, beta);
    // Problem is generated inside STARS_gen_ss_blrformat
    matrix = STARS_blr__compress_algebraic_svd(format, tol);
    //STARS_BLRmatrix_info(matrix);
    STARS_BLRmatrix_free(matrix);
    //STARS_BLR_info(format);
    STARS_BLR_free(format);
    return 0;
}
