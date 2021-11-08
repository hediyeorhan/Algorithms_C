/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Edge {
	int src, dest, weight;
};


struct Graph {
	int V, E;

	struct Edge* edge;
};


struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = (struct Graph*)(malloc(sizeof(struct Graph)));
	graph->V = V;
	graph->E = E;

	graph->edge = (struct Edge*)malloc(sizeof( struct Edge));

	return graph;
}

struct subset {
	int parent;
	int rank;
};


int find(struct subset subsets[], int i)
{

	if (subsets[i].parent != i)
		subsets[i].parent
			= find(subsets, subsets[i].parent);

	return subsets[i].parent;
}


void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);


	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;


	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}


int myComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight > b1->weight;
}


void KruskalMST(struct Graph* graph)
{
	int V = graph->V;
	struct Edge
		result[V];
	int e = 0;
	int i = 0;


	qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
		myComp);

	// Allocate memory for creating V ssubsets
	struct subset* subsets
		= (struct subset*)malloc(V * sizeof(struct subset));

	// Create V subsets with single elements
	for (int v = 0; v < V; ++v) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	// Number of edges to be taken is equal to V-1
	while (e < V - 1 && i < graph->E) {
		// Step 2: Pick the smallest edge. And increment
		// the index for next iteration
		struct Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		// If including this edge does't cause cycle,
		// include it in result and increment the index
		// of result for next edge
		if (x != y) {
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
		// Else discard the next_edge
	}

	// print the contents of result[] to display the
	// built MST
	printf(
		"Following are the edges in the constructed MST\n");
	int minimumCost = 0;
	for (i = 0; i < e; ++i)
	{
		printf("%d -- %d == %d\n", result[i].src,
			result[i].dest, result[i].weight);
		minimumCost += result[i].weight;
	}
	printf("Minimum Cost Spanning tree : %d",minimumCost);
	return;
}

// Driver program to test above functions
int main()
{
	int V = 4; // Number of vertices in graph
	int E = 5; // Number of edges in graph
	struct Graph* graph = createGraph(V, E);

	// add edge 0-1
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;
	graph->edge[0].weight = 10;

	// add edge 0-2
	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 6;

	// add edge 0-3
	graph->edge[2].src = 0;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 5;

	// add edge 1-3
	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 15;

	// add edge 2-3
	graph->edge[4].src = 2;
	graph->edge[4].dest = 3;
	graph->edge[4].weight = 4;

	KruskalMST(graph);

	return 0;
}
*/

#include<stdio.h>

#define MAX 30

typedef struct edge
{
	int u,v,w;
}edge;

typedef struct edgelist
{
	edge data[MAX];
	int n;
}edgelist;

edgelist elist;

int G[MAX][MAX],n;
edgelist spanlist;

void kruskal();
int find(int belongs[],int vertexno);
void union1(int belongs[],int c1,int c2);
void sort();
void print();

void kruskal()
{
	int belongs[MAX],i,j,cno1,cno2;
	elist.n=0;

	for(i=1;i<n;i++)
		for(j=0;j<i;j++)
		{
			if(G[i][j]!=0)
			{
				elist.data[elist.n].u=i;
				elist.data[elist.n].v=j;
				elist.data[elist.n].w=G[i][j];
				elist.n++;
			}
		}

	sort();

	for(i=0;i<n;i++)
		belongs[i]=i;

	spanlist.n=0;

	for(i=0;i<elist.n;i++)
	{
		cno1=find(belongs,elist.data[i].u);
		cno2=find(belongs,elist.data[i].v);

		if(cno1!=cno2)
		{
			spanlist.data[spanlist.n]=elist.data[i];
			spanlist.n=spanlist.n+1;
			union1(belongs,cno1,cno2);
		}
	}
}

int find(int belongs[],int vertexno)
{
	return(belongs[vertexno]);
}

void union1(int belongs[],int c1,int c2)
{
	int i;

	for(i=0;i<n;i++)
		if(belongs[i]==c2)
			belongs[i]=c1;
}

void sort()
{
	int i,j;
	edge temp;

	for(i=1;i<elist.n;i++)
		for(j=0;j<elist.n-1;j++)
			if(elist.data[j].w>elist.data[j+1].w)
			{
				temp=elist.data[j];
				elist.data[j]=elist.data[j+1];
				elist.data[j+1]=temp;
			}
}

void print()
{
	int i,cost=0;

	for(i=0;i<spanlist.n;i++)
	{
		printf("\n%d\t%d\t%d",spanlist.data[i].u,spanlist.data[i].v,spanlist.data[i].w);
		cost=cost+spanlist.data[i].w;
	}

	printf("\n\nCost of the spanning tree=%d",cost);
}

void main()
{
	int i,j,total_cost;

	printf("\nEnter number of vertices:");

	scanf("%d",&n);

	printf("\nEnter the adjacency matrix:\n");

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);

	kruskal();
	print();
}
