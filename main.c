#include <stdlib.h>
#include <stdio.h>
#define NIL -1
#define FALSE 0
#define TRUE 1

/*******************************************************************************
*                         GRAPH Abstract Data Type                             *
*******************************************************************************/

typedef struct {
    int v;
    int w;
} Edge;

typedef struct node *link;

struct node {
    int v;
    link next;
};

struct graph {
    int V;
    int E;
    link *adj;
};

typedef struct graph *Graph;

Edge newEDGE(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

link newLINK(int v, link next) {
    link x = malloc(sizeof(*x));
    x -> v = v;
    x -> next = next;
    return x;
}

/* Initialization of the graph. 
Memory allocation and NULL initialization of V vertices.
Operation complexity: O(V) */

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof(*G));
    G -> V = V;
    G -> E = 0;
    G -> adj = malloc(V*sizeof(link));
    for (v = 0; v < V; v++) { /* Complexity O(V) */
        G->adj[v] = NULL;
    }
    return G;
}

/* Insert an edge: O(1)*/
void GRAPHinsertE(Graph G, Edge e) {
    int v = (e.v - 1), w = (e.w - 1);
    G -> adj[v] = newLINK(w, G -> adj[v]);
    G -> adj[w] = newLINK(v, G -> adj[w]);
    G -> E++;
}


/*******************************************************************************
*                   Algorithm to find Articulation Points                      *
*******************************************************************************/

/* We use 3 static ints: apcount to store the total number of articulation
points (fundamental people), min to store the minimum articulation point and 
max to store the maximum */
static int apcount, min = -2, max = -2;

void searchArticulationPoints(Graph G, int vertex, int discoveryTime[],
                              int low[], int parent[], int visitTime,
                              int isArticulationPoint[]) {

    link adjVertex;
    int children = 0;

    discoveryTime[vertex] = visitTime++;
    low[vertex] = discoveryTime[vertex];

    /* For each adjacent vertex of the one currently being studied.
       Complexity: O(E) */
    for (adjVertex = G->adj[vertex]; adjVertex != NULL; adjVertex = adjVertex->next)

    /* If it hasn't been discovered yet */
    if (discoveryTime[adjVertex->v] == NIL) {
        children++; /* The number of children is increased */
        parent[adjVertex->v] = vertex; /* And its predecessor is updated */
        /* We then proceed to the DFS step of the algorithm */
        searchArticulationPoints(G, adjVertex->v, discoveryTime, low,
                                 parent, visitTime, isArticulationPoint);

        if (low[vertex] > low[adjVertex->v])
        /* If the low value of the vertex is higher than the low value of
        one of his adjacent vertices, it is updated as the lower value*/
        low[vertex] = low[adjVertex->v];

        /* A vertex is an articulation point if:
        - It's not the root of a DFS tree and its
        discoveryTime is less or equal to the low value of his adjacent vertices */
        if (low[adjVertex->v] >= discoveryTime[vertex] && parent[vertex] != NIL
            && isArticulationPoint[vertex] == FALSE) {

            isArticulationPoint[vertex] = TRUE;
            apcount++;
            if(vertex < min || min == -2)
                min = vertex;
            if(vertex > max)
                max = vertex;
        }

        /* -It's the root of a DFS tree and has 2 or more children */
        else if (children > 1 && parent[vertex] == NIL
            && isArticulationPoint[vertex] == FALSE) {

            isArticulationPoint[vertex] = TRUE;
            apcount++;
            if(vertex < min || min == -2)
                min = vertex;
            if(vertex > max)
                max = vertex;
        }
    }
    /* If the adjacent vertex has already been discovered,
    its low value is updated (if needed) */
    else if (adjVertex->v != parent[vertex]) {
        if (low[vertex] > discoveryTime[adjVertex->v])
        low[vertex] = discoveryTime[adjVertex->v];
    }

}

void GRAPHsearch(Graph G) {


    int visitTime = 0; /* The current time in a DFS search*/
    int numberOfVertices = G -> V; /* The number of vertices in the graph */
    int vertex; /* The current vertex*/

    /* Following is the declaration of 4 auxiliary vectors to store properties of
    vertices: */
    int discoveryTime[numberOfVertices]; /* The discovery time in a DFS */
    int low[numberOfVertices]; /* The low value: the lowest discovery time 
    reachable from the vertex */
    int parent[numberOfVertices]; /* The parent of the vertex in a DFS */
    int isArticulationPoint[numberOfVertices]; /* Pseudo-boolean vector: stores if 
    the vertex has already been declared an articulation point (TRUE) or not (FALSE)*/

    /* First we initialize the discovery time, parents, and articulation point
    properties of each vertex (O(V))*/ 
    for (vertex = 0; vertex < numberOfVertices; vertex++) {
        discoveryTime[vertex] = NIL;
        parent[vertex] = NIL;
        isArticulationPoint[vertex] = FALSE;
    }

    /* We then proceed to do the recursive depth first search of the graph, starting in
    vertex 0 (which is actually vertex 1) */
    for (vertex = 0; vertex < G->V; vertex++) /* O(V) */
    if (discoveryTime[vertex] == NIL)
    searchArticulationPoints(G, vertex, discoveryTime, low,
                             parent, visitTime, isArticulationPoint); /*O(E)*/
    /* TOTAL complexity: O(|V|+|E|) */
}

/*******************************************************************************
*                                Main function                                 *
*******************************************************************************/

int main() {

    /* We declare an int v to store the number of people in the network (vertices)
    and reutilize to save one vertex of the edge, int u to store the other vertex
    of the edge and an int e to the number of connections between people (edges)*/
    int v, e, u; /*v = N; e = L*/

    /* First we read from stdin the number of vertices and edges to initialize the
    graf */
    scanf("%d %d", &v, &e);
    Graph network = GRAPHinit(v);

    /* We proceed to read all the connections from the input */
    for (; e>0; e--) {
        scanf("%d %d", &u, &v);
        Edge edge = newEDGE(u, v);
        GRAPHinsertE(network, edge);
    }

    /* The graph search funtion finds the Articulation Points of a graph
    (fundamental people of the network) */
    GRAPHsearch(network);

    printf("%d\n", apcount);
    printf("%d %d\n", min + 1, max + 1);

    return 0;
}
