#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "rmq-offline.h"

double gettime( void )
{
    struct timeval ttime;
    gettimeofday( &ttime , 0 );
    return ttime.tv_sec + ttime.tv_usec * 0.000001;
};

int main( int argc, char *argv[] )
{
    if ( argc != 3 )
    {	
    	fprintf( stderr, "%s [INT n] [INT q]\n", argv[0]);
        return ( 1 ); 
    }

    double start, end;
    srand( time(NULL) );

    INT n = atoi(argv[1]);
    INT * A = ( INT * ) calloc ( n, sizeof(INT) );

    for ( INT i= 0; i < n; i++ )
   	A[i] = i;
    for ( INT i = 0; i < (n/2); i++ )
    {	
   	INT a = rand() % n;
   	INT b = rand() % n;
        INT temp = A[a];
        A[a] = A[b];
        A[b] = temp;  
    }

    INT q = atoi(argv[2]);
    Query * Q = ( Query * ) calloc ( q, sizeof( Query ) );
    for ( INT i = 0; i < q; i++ )
    {	
   	INT a = rand() % n;
   	INT b = rand() % n;
   	if ( a <= b ) 
        {
           Q[i] . L = a; 
           Q[i] . R = b;
        }
        else 
        {
           Q[i] . L = b; 
           Q[i] . R = a;
        }
    }


    fprintf( stderr, "n = %ld, q = %ld\n", n, q);
    start = gettime();
    rmq_offline ( A, n, Q, q );
    end = gettime();
    fprintf( stderr, "%lf secs\n", end - start);

    free ( A );
    free ( Q );

    return ( 0 );
}
