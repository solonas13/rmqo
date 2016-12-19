#include <stdio.h>
#include "rmq-offline.h"

int main( int argc, char *argv[] )
{
    // Create an array of size 10 and fill it up
    INT n = 10;
    INT * A = ( INT * ) calloc ( n, sizeof(INT) );

    A[0] = 4; A[1] = 3; A[2] = 5; A[3] = 9; A[4] = 8;
    A[5] = 1; A[6] = 2; A[7] = 0; A[8] = 6; A[9] = 7;
    
    // Print out the array
    for ( INT i = 0; i < n; i++ )
    {	
      fprintf( stderr, "%ld ", A[i]);
    }		
    fprintf( stderr, "\n" );

    // Prepare some queries: RMQ(3,9) and RMQ(2,5)
    INT q = 2;
    Query * Q = ( Query * ) calloc ( q, sizeof( Query ) );

    Q[0] . L = 3; Q[0] . R = 9;	
    Q[1] . L = 2; Q[1] . R = 5;	

    // Answer the queries!
    rmq_offline ( A, n, Q, q );

    // Print out the answers
    for ( INT i = 0; i < q; i++ )
    {	
      fprintf( stderr, "RMQ(%ld,%ld)=%ld\n",
                  Q[i].L,
                  Q[i].R,
                  Q[i].O);
    }		

    // Free the memory
    free ( A );
    free ( Q );

    return ( 0 );
}
