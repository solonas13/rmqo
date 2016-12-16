/**
    rmqo: Answering a small batch of RMQs in practice
    Copyright (C) 2016 Mai Alzamel and Solon P. Pissis

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include "rmq-offline.h"

/* It takes n + O(q log q) time and uses O(q) extra space */ 
INT rmq_offline ( INT * A, INT n, Query * Q, INT q )
{
    INT s = (4 * q) + 1;
    if ( s > n ) s = n;
    INT * AQ = ( INT* ) calloc( s , sizeof(INT) );
    INT * Af = ( INT* ) calloc( s , sizeof(INT) );
    Query * Q_Prime = ( Query * ) calloc(q, sizeof(Query));

    contract( A, n, Q, q, AQ, &s, Af, Q_Prime );

    answer_rmqs ( AQ, s, Q, q, Q_Prime, Af );

    free( AQ );
    free( Af );
    free( Q_Prime );

    return ( 1 );
}

INT answer_rmqs ( INT * A, INT n, Query * Q, INT q, Query * Q_Prime,  INT * Af )
{
    /* Calculates the max number t of buckets based on Q_Prime */
    INT t = 0;	
    for ( INT i = 0; i < q; i++ )	
    {
	INT x = Q_Prime[i] . R - Q_Prime[i] . L;
	if ( x > 0 )
	{
		INT s = flog2( x );
		if ( s > t ) t = s;
	}
    }
    t = t + 1;

    /* Bucket sort the queries */
    INT * c = ( INT * ) calloc( t , sizeof( INT ) );
    List ** B = ( List ** ) calloc( t , sizeof( List * ) );
    for ( INT i = 0; i < t; i++) B[i] = NULL;

    for ( INT i = 0; i < q; i++ )	
    {
    	if ( Q[i] . L == Q[i] . R ) 
		Q[i]. O = Q[i] . L;
        else
        {
		INT s = flog2( Q_Prime[i] . R - Q_Prime[i] . L ); //get the id of the bucket
		if ( c[s] == 0 ) //if the bucket is empty start a linked list
		{
			B[s] = ( List * ) malloc( sizeof(List) );
           		List * newNode= ( List * ) malloc(sizeof(List));
           		newNode -> pos  = i;
           		newNode -> next = NULL;
			B[s] = newNode;
			c[s]++;
		}
		else		//add query id to the front of the linked list
		{
			List * head = B[s];
           		List * newNode= ( List * ) malloc(sizeof(List));
			newNode -> pos = i;
			newNode -> next = head;
			B[s] = newNode;
		}
	}
    }
    free( c );

    Tuples * D = ( Tuples * ) calloc( ( INT ) n, sizeof( Tuples ) );
    for ( INT i = 0; i < n; i++ )	{D[i] . a = A[i]; D[i] . p = i;}
    
    for ( INT k = 0; k < t; k++ )	
    {
        INT r = ( INT ) ( 1 << k );
        List * head = B[k];
	while ( head != NULL ) //loop through buckets
	{
		INT i = head -> pos;
		if ( D[Q_Prime[i] . L] . a < D[Q_Prime[i] . R - r + 1] . a ) 
			Q[i] . O = Af[D[Q_Prime[i] . L] . p]; 
		else	
			Q[i] . O = Af[D[Q_Prime[i] . R - r + 1] . p]; 
		head = head -> next;
    	}
	for ( INT i = 0; i < n; i++ )	
	{
		INT j = i + r;
		if ( j < n && D[i] . a > D[j] . a )
		{
			D[i] . a = D[j] . a;
			D[i] . p = D[j] . p;
		}
	}
    }
    
    for ( INT i = 0; i < t; i ++ )
    {
       List * head = B[i];
       List * tmp;
       while ( head != NULL )
       {
          tmp = head->next;          // advance head to next element.
          free ( head );                // delete saved pointer.
          head = tmp;
       }
    }

    free( B );
    free( D );
    
    return ( 1 );
}

INT contract( INT * A, INT n, Query * Q, INT q, INT * AQ, INT * s, INT * Af, Query * Q_Prime )
{
    /* Defines an array to store the original values (of potential 2q indices) */
    INT * l_0 = ( INT* ) calloc( 2 * q, sizeof(INT) );

    /*Defines an array to store linked lists */
    List ** l_1 = ( List ** ) calloc( 2 * q , sizeof( List * ) );

    /*find the Max value in array A*/
    INT max = A[0];
    for( INT i = 1; i < n; i++ )
        if(A[i]>max) max=A[i];

    /* Marking*/
    marking( A, n, max, Q, q, l_0, l_1 );

    /* Create array AQ */
    create( A, n, max, Q, q, l_0, l_1, AQ, s, Af, Q_Prime );
    
    /* Recover Array A */
    recover( A, n, AQ, (* s), Af );
    
    /*Free the memory*/
    free(l_0);
    for ( INT i = 0; i < 2 * q; i ++ )
    {
       List * head = l_1[i];
       List * tmp;
       while ( head != NULL ) 
       { 
          tmp = head->next;          // advance head to next element.
          free (head);                // delete saved pointer.
          head = tmp;
       }
    }
    free(l_1);
  
  return ( 1 );
}

INT recover ( INT * A, INT n, INT * AQ, INT s, INT * Af )
{
	for ( INT j = 0; j < s; j++ )	A[Af[j]] = AQ[j];
  	return ( 1 );
}

INT create ( INT * A, INT n, INT max, Query * Q, INT q, INT * l_0, List ** l_1, INT * AQ, INT * s, INT * Af, Query * Q_Prime)
{

	INT min = A[0]; 
	INT temp = 0;
	INT t = 0;

	for ( INT i = 0; i < q; i++ )
	{
		Q_Prime[i] . L = -1;
		Q_Prime[i] . R = -1;
	}

    	for ( INT i = 0; i < n; i++ )
    	{
		if ( A[i] > max )
		{
			if ( Q_Prime[l_1[A[i]%(2*q)]->pos] . L <= -1 )
				Q_Prime[l_1[A[i]%(2*q)]->pos] . L = t;
			else
				if ( Q_Prime[l_1[A[i]%(2*q)]->pos].R <= -1 )
					Q_Prime[l_1[A[i]%(2*q)]->pos].R = t;
		    
			/*If there is a linked list */
			List * head = l_1[A[i]%(2*q)];
			while ( head->next != NULL )
			{
				head = head->next;
				if ( Q_Prime[head->pos].L <= -1 )
					Q_Prime[head->pos].L = t;
				else
					if (Q_Prime[head->pos].R<= -1)
						Q_Prime[head->pos].R = t;
			}

			AQ[t] = l_0[A[i]%(2*q)];
			Af[t] = i;
			t++;
		}
		else
		{	
			/*To find the min between non-marked positions (after a marked position) and throw away anything after the last marked position*/
			if ( i > 0 && A[i - 1] > max )
			{
			      min = A[i];
			      temp = i;
			}	

			if ( A[i] <= min )
			{
			       min = A[i];
			       temp = i;  
			}

			/*copy the marked position to AQ and store the original position in AF*/
			if ( i < n - 1 && A[i+1]> max )
			{
				AQ[t] = min;
				Af[t] = temp;
				t++;
			}
		}
    	}

	( * s ) = t;
    
    	return ( 1 );
}
    

INT marking( INT * A, INT n, INT max, Query * Q, INT q, INT * l_0, List ** l_1 )
{
    INT k = 1; //counter
    
    for ( INT i = 0; i < 2 * q; i++) l_1[i] = NULL;
    
    /* Changing the values of A with ( k + max ) */
    for ( INT m = 0; m < q; m++) 
    {
        
        
        /****************************Adding all i's indices in queries in L_1************************/
        INT start_point = Q[m].L;

        /*Position is marked add the rest of the queries in the Linked list at the front*/
        if( A[start_point] > max )
        {
            //add to the front
            List * head = l_1[(A[start_point])%(2*q)];
            List * newNode = ( List * )malloc(sizeof(List));
            newNode->pos=m;
            newNode->next=head;
            l_1[(A[start_point])%(2*q)]=newNode;
         }
        
        if(A[start_point]<= max)
        {
           l_0[((k+max) %(2*q))]=A[start_point];
           A[start_point] = k + max; // update with counter
           //start a linked list
           l_1[((k+max) %(2*q))] = ( List * )malloc(sizeof(List));
           List * newNode = ( List * ) malloc(sizeof(List));
           newNode->pos=m;
           newNode->next=NULL;
           l_1[((k+max) %(2*q))]= newNode;
           k++;
        }
    
        /****************************Adding all j's indices in queries in L_1************************/
        INT end_point=Q[m].R;

        //Position is marked add the rest of the queries in the Linked list at the front
        if(A[end_point]> max)
        {
            //add to the front
            List * head = l_1[(A[end_point])%(2*q)]; 
            List * newNode=(List*)malloc(sizeof(List));
            newNode->pos=m;
            newNode->next=head;
            l_1[(A[end_point])%(2*q)]=newNode;
        }
        
        if(A[end_point]<= max){
            
            l_0[((k+max) %(2*q))]=A[end_point];
            A[end_point]=k + max;
            //start a linked list
            l_1[((k+max) %(2*q))] = (List*)malloc(sizeof(List));
            List * newNode= (List*)malloc(sizeof(List));
            newNode->pos=m;
            newNode->next=NULL;
            l_1[((k+max) %(2*q))]= newNode;
            k++;
        }
        
    }

    return ( 1 );
}
