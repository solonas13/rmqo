#include <stdio.h>
#include "rmq-offline.h"

struct Node
{
    INT data;
    Node * left, * right;
};

void TreeToArray ( Node * node, INT * A, INT * i );
void deleteTree ( Node * node );
Node* newNode( INT data);

int main( int argc, char *argv[] )
{
	/*
     		Let's construct a binary tree!
            0
          /  \
         1    2
       /  \
      3    4

	*/
 
    Node *root = newNode(0);
    root->left        = newNode(1);
    root->right       = newNode(2);
    root->left->left  = newNode(3);
    root->left->right = newNode(4);

    // Some LCA Queries to answer: LCA(3,4), LCA(0,2), and LCA(1,2)
    INT q = 3;
    Query * Q = ( Query * ) calloc ( q, sizeof( Query ) );
    Q[0] . L = 3; Q[0] . R = 4;	
    Q[1] . L = 0; Q[1] . R = 2;
    Q[2] . L = 1; Q[1] . R = 2;

    // Transform the tree to an array via a DFS in-order traversal
    INT n = 5;
    INT * A = ( INT* ) calloc( n , sizeof(INT) );
    INT k = 0;
    TreeToArray ( root, A, &k );
    deleteTree ( root );

    // Record the indices of the node labels 0,1,...,4
    INT * invA = ( INT* ) calloc( n , sizeof(INT) );
    for ( INT i = 0; i < n; i ++ )  invA[A[i]] = i;

    Query * Q_lca = ( Query * ) calloc( q , sizeof(Query) );
    for ( INT i = 0; i < q; i ++ )  
    {
       if (invA[Q[i] . L] < invA[Q[i] . R])
       {
	  Q_lca[i] . L = invA[Q[i] . L];
	  Q_lca[i] . R = invA[Q[i] . R];
       }
       else
       {
          Q_lca[i] . L = invA[Q[i] . R];
	  Q_lca[i] . R = invA[Q[i] . L];
       }
    }
    free( invA );
 
    // Answer the queries!
    rmq_offline ( A, n, Q_lca, q );

    // Transform the RMQ answers back to node labels
    for ( INT i = 0; i < q; i++ )	Q[i] . O = A[Q_lca[i] . O];

    // Printout the LCAs
    for ( INT i = 0; i < q; i++ )
    {	
      fprintf( stderr, "LCA(%ld,%ld)=%ld\n",
                  Q[i].L,
                  Q[i].R,
                  Q[i].O);
    }		

    // Free the memory
    free ( Q );
    free( Q_lca );
    free( A );


    return ( 0 );
}

void deleteTree ( Node * node )
{
    if(node->left) deleteTree(node->left);
    if(node->right) deleteTree(node->right);
    free ( node );
}

/* Tree to Array */
void TreeToArray ( Node * node, INT * A, INT * i )
{
    if (node == NULL) return;
    TreeToArray (node->left, A, i );
    A[*i] = node -> data; (*i)++;
    TreeToArray (node->right, A, i );
}

Node* newNode( INT data)
{
    Node* node = ( Node * ) calloc ( 1, sizeof( Node ));
    node->data = data;
    node->left = node->right = NULL;
    return(node);
}
