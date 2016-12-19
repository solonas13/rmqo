#include <stdio.h>
#include "rmq-offline.h"

int main( int argc, char *argv[] )
{
	/*
     		Let's construct the Cartesian tree of sequence 4, 1, 2, 3, 0
           0
          /  
         4    
          \
           1
	    \
             2
              \
               3	
	*/
 
    // Some LCA Queries to answer: LCA(3,4), LCA(0,2), LCA(1,2), and LCA(2,3)
    INT q = 4;
    Query * Q_lca = ( Query * ) calloc ( q, sizeof( Query ) );
    Q_lca[0] . L = 3; Q_lca[0] . R = 4;	
    Q_lca[1] . L = 0; Q_lca[1] . R = 2;
    Q_lca[2] . L = 1; Q_lca[2] . R = 2;
    Q_lca[3] . L = 2; Q_lca[3] . R = 3;

    // Write down the Euler tour, the depths array, and the representative array
    INT n = 5;
    INT s = (2 * n)  - 1;
    INT * E = ( INT * ) calloc( s , sizeof(INT) );
    E[0] = 0; E[1] = 4; E[2] = 1; E[3] = 2; E[4] = 3; E[5] = 2; E[6] = 1; E[7] = 4; E[8] = 0;
    INT * L = ( INT * ) calloc( s , sizeof(INT) );
    L[0] = 0; L[1] = 1; L[2] = 2; L[3] = 3; L[4] = 4; L[5] = 3; L[6] = 2; L[7] = 1; L[8] = 0;
    INT * R = ( INT * ) calloc( n , sizeof(INT) );
    R[0] = 0; R[1] = 2; R[2] = 3; R[3] = 4; R[4] = 1;

    Query * Q = ( Query * ) calloc( q , sizeof( Query ) );
    for ( INT i = 0; i < q; i ++ )  
    {
       if ( R[Q_lca[i] . L] < R[Q_lca[i] . R] )
       {
	  Q[i] . L = R[Q_lca[i] . L];
	  Q[i] . R = R[Q_lca[i] . R];
       }
       else
       {
          Q[i] . L = R[Q_lca[i] . R];
	  Q[i] . R = R[Q_lca[i] . L];
       }
    }
 
    // Answer the queries!
    rmq_offline ( L, s, Q, q );

    // Transform the RMQ answers back to node labels
    for ( INT i = 0; i < q; i++ )	Q_lca[i] . O = E[Q[i] . O];

    // Printout the LCAs
    for ( INT i = 0; i < q; i++ )
    {	
      fprintf( stderr, "LCA(%ld,%ld)=%ld\n",
                  Q_lca[i].L,
                  Q_lca[i].R,
                  Q_lca[i].O);
    }		

    // Free the memory
    free ( Q );
    free( Q_lca );
    free( L );
    free( E );
    free( R );


    return ( 0 );
}
