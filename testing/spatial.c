#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stars.h"
#include "stars-spatial.h"

int main(int argc, char **argv)
    // Example of how to use STARS library for spatial statistics.
    // For more information on STARS structures look inside of header files.
{
    if(argc < 8)
    {
        printf("%d\n", argc);
        printf("electrostatics.out row_blocks col_blocks block_size maxrank "
                "tol beta KADIR\n");
        exit(0);
    }
    int row_blocks = atoi(argv[1]), col_blocks = atoi(argv[2]);
    int block_size = atoi(argv[3]), maxrank = atoi(argv[4]);
    double tol = atof(argv[5]), beta = atof(argv[6]);
    int KADIR = atoi(argv[7]);
    printf("rb=%d, cb=%d, bs=%d, mr=%d, tol=%e, beta=%f, KADIR=%d\n",
            row_blocks, col_blocks, block_size, maxrank, tol, beta, KADIR);
    STARS_Problem *problem;
    STARS_BLR *format;
    STARS_BLRmatrix *matrix = NULL;
    while(matrix == NULL)
    {
        format = STARS_gen_ss_blrformat(row_blocks, col_blocks, block_size, beta);
        // Problem is generated inside STARS_gen_ss_blrformat
        matrix = STARS_blr__compress_algebraic_svd(format, maxrank, tol, KADIR);
        if(matrix == NULL)
        {
            free(format->problem->row_data);
            free(format->problem);
            STARS_BLR_free(format);
        }
    }
    printf("Measuring error!\n");
    STARS_BLRmatrix_error(matrix);
    //STARS_BLRmatrix_info(matrix);
    STARS_BLRmatrix_printKADIR(matrix);
    STARS_BLRmatrix_free(matrix);
    //STARS_BLR_info(format);
    STARS_BLR_free(format);
    return 0;
}
