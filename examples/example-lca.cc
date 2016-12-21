#include <stdio.h>
#include "rmq-offline.h"

int main( int argc, char *argv[] )
{
	/*

     	Let's consider the following binary tree:

	           0
	          /  
	         4    
	        / \
	       5   1
		    \
       		     2
         	      \
                       3	
               
        In fact we will consider its Euler tour representation...
	*/

    // Write down the Euler tour array, the depths array, and the representative array
    INT n = 6;
    INT s = (2 * n)  - 1;
    INT * E = ( INT * ) calloc( s , sizeof(INT) );
    E[0] = 0; E[1] = 4; E[2] = 5; E[3] = 4; E[4] = 1; E[5] = 2; E[6] = 3; E[7] = 2; E[8] = 1; E[9] = 4; E[10] = 0;
    INT * L = ( INT * ) calloc( s , sizeof(INT) );
    L[0] = 0; L[1] = 1; L[2] = 2; L[3] = 1; L[4] = 2; L[5] = 3; L[6] = 4; L[7] = 3; L[8] = 2; L[9] = 1; L[10] = 0;
    INT * R = ( INT * ) calloc( n , sizeof(INT) );
    R[0] = 0; R[1] = 4; R[2] = 5; R[3] = 6; R[4] = 1;
 
    // Some LCA Queries to answer: LCA(3,4), LCA(0,2), LCA(1,2), and LCA(2,3)
    INT q = 4;
    Query * Q_lca = ( Query * ) calloc ( q, sizeof( Query ) );
    Q_lca[0] . L = 3; Q_lca[0] . R = 4;	
    Q_lca[1] . L = 0; Q_lca[1] . R = 2;
    Q_lca[2] . L = 1; Q_lca[2] . R = 2;
    Q_lca[3] . L = 2; Q_lca[3] . R = 3;


    // Translate the LCA queries to RMQs
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

    // Transform the RMQ answers back to LCA answers
    for ( INT i = 0; i < q; i++ )	Q_lca[i] . O = E[Q[i] . O];

    // Print out the LCAs
    for ( INT i = 0; i < q; i++ )
    {	
      fprintf( stderr, "LCA(%ld,%ld)=%ld\n",
                  Q_lca[i].L,
                  Q_lca[i].R,
                  Q_lca[i].O);
    }		

    // Free the memory
    free ( Q );
    free ( Q_lca );
    free ( L );
    free ( E );
    free ( R );

    return ( 0 );
}
