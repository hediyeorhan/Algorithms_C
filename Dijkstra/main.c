/*// Dijkstra's Algorithm in C

#include <stdio.h>
#define INFINITY 9999
#define MAX 10

void Dijkstra(int Graph[MAX][MAX], int n, int start);

void Dijkstra(int Graph[MAX][MAX], int n, int start) {
  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;

  // Creating cost matrix
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i < n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while (count < n - 1) {
    mindistance = INFINITY;

    for (i = 0; i < n; i++)
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }

  // Printing the distance
  for (i = 0; i < n; i++)
    if (i != start) {
      printf("\nDistance from source to %d: %d", i, distance[i]);
    }
}
int main() {
  int Graph[MAX][MAX], i, j, n, u;
  n = 7;

  Graph[0][0] = 0;
  Graph[0][1] = 0;
  Graph[0][2] = 1;
  Graph[0][3] = 2;
  Graph[0][4] = 0;
  Graph[0][5] = 0;
  Graph[0][6] = 0;

  Graph[1][0] = 0;
  Graph[1][1] = 0;
  Graph[1][2] = 2;
  Graph[1][3] = 0;
  Graph[1][4] = 0;
  Graph[1][5] = 3;
  Graph[1][6] = 0;

  Graph[2][0] = 1;
  Graph[2][1] = 2;
  Graph[2][2] = 0;
  Graph[2][3] = 1;
  Graph[2][4] = 3;
  Graph[2][5] = 0;
  Graph[2][6] = 0;

  Graph[3][0] = 2;
  Graph[3][1] = 0;
  Graph[3][2] = 1;
  Graph[3][3] = 0;
  Graph[3][4] = 0;
  Graph[3][5] = 0;
  Graph[3][6] = 1;

  Graph[4][0] = 0;
  Graph[4][1] = 0;
  Graph[4][2] = 3;
  Graph[4][3] = 0;
  Graph[4][4] = 0;
  Graph[4][5] = 2;
  Graph[4][6] = 0;

  Graph[5][0] = 0;
  Graph[5][1] = 3;
  Graph[5][2] = 0;
  Graph[5][3] = 0;
  Graph[5][4] = 2;
  Graph[5][5] = 0;
  Graph[5][6] = 1;

  Graph[6][0] = 0;
  Graph[6][1] = 0;
  Graph[6][2] = 0;
  Graph[6][3] = 1;
  Graph[6][4] = 0;
  Graph[6][5] = 1;
  Graph[6][6] = 0;

  u = 0;
  Dijkstra(Graph, n, u);

  return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
int G[20][20] , distance[20] , inSet[20] , q[20] , parent[20] ;
void print( int V )
{
    int i ;
    for ( i = 0 ; i < V ; i++ )
        printf("i = %d parent = %d distance from source = %d \n", i + 1 , parent[i] , distance[i] ) ;
}
int Q( int V )
{
    int sum = 0 , i ;
    for( i = 0 ; i < V ; i++ )
        sum += q[i] ;
    return sum ;
}
int extractMin( int V )
{
    int i , idx , min = 1000 ;
    for ( i = 0 ; i < V ; i++ )
    {
        if ( distance[i] <= min && inSet[i] == 0 )
            min = distance[i] , idx = i ;
    }
    q[idx] = 0 ;
    return idx ;
}
void dijkstra ( int S , int V )
{
    int u , i , check_empty = Q(V);

    while( check_empty >0 )
    {
        u = extractMin(V) ;

        inSet[u] = 1 ;
        q[u] = 0 ;
        for( i = 0 ; i < V ; i++ )
        {
            if( G[u][i] > 0 )
            {
                if( distance[u] + G[u][i] < distance[i] )
                    distance[i] = distance[u] + G[u][i] , parent[i] = u + 1 ;
            }
        }
        check_empty = Q(V);
    }

    print(V);
}
int main()
{
    int V , i , j , S;
    printf ( "Enter no. of vertices: " ) ;
    scanf ( "%d" , &V ) ;

    printf ( "Enter graph in matrix form:\n" ) ;
    for ( i = 0 ; i < V ; i++ )
    {
        for( j = 0 ; j < V ; j++ )
            scanf( "%d" , &G[i][j] );
    }
    for ( i = 0 ; i < V ; i++ )
        distance[i] = 1000 , inSet[i] = 0 , q[i] = 1 , parent[i] = -1 ;

    printf ( "Enter the source vertex: " ) ;
    scanf ( "%d" , &S ) ;
    distance[ S - 1 ] = 0 ;
    dijkstra ( S , V ) ;
    return 0;
}
