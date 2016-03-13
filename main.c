#include <stdlib.h>
#include <stdio.h>
#define NIL -1
#define FALSE 0
#define TRUE 1

/*******************************************************************************
*                         GRAPH Abstract Data Tipe                             *
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

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof(*G));
    G -> V = V;
    G -> E = 0;
    G -> adj = malloc(V*sizeof(link));
    for (v = 0; v < V; v++) {
        G->adj[v] = NULL;
    }
    return G;
}
void GRAPHinsertE(Graph G, Edge e) {
    int v = (e.v - 1), w = (e.w - 1);
    G -> adj[v] = newLINK(w, G -> adj[v]);
    G -> adj[w] = newLINK(v, G -> adj[w]);
    G -> E++;
}

int GRAPHedges(Edge a[], Graph G) {
    int v, E = 0;
    link t;
    for (v = 0; v < G -> V; v++) {
        for (t = G -> adj[v]; t != NULL; t = t -> next) {
            if (v < t -> v) {
                a[E++] = newEDGE(v, t -> v);
            }
        }
    }
    return E;
}

void GRAPHshow(Graph G) {
    int v;
    link t;
    printf("%d vertices, %d edges\n", G -> V, G -> E);
    for (v = 0; v < G -> V; v++) {
        printf("%2d:", v + 1);
        for (t = G -> adj[v]; t != NULL; t = t -> next) {
            printf(" %2d", (t -> v) + 1);
        }
        printf("\n");
    }
}

/*******************************************************************************
*                   Algorithm to find Articulation Points                      *
*******************************************************************************/

/* We use 3 static ints: apcount to store the total number of articulation
points (fundamental people), min to store the minimum vertex and max to the
maximum vertex */
static int apcount, min = -1, max = -1;

void searchArticulationPoints(Graph G, int vertex, int discoveryTime[],
                              int low[], int parent[], int visitTime,
                              int isArticulationPoint[]) {

    link adjVertex;
    int children = 0;

    discoveryTime[vertex] = visitTime++;
    low[vertex] = discoveryTime[vertex];

    /* For each adjacent vertex of the one currently being studied */
    for (adjVertex = G->adj[vertex]; adjVertex != NULL; adjVertex = adjVertex->next)

    /* If it hasn't been discovered yet */
    if (discoveryTime[adjVertex->v] == NIL) {
        children++; /* The number of children is increased */
        parent[adjVertex->v] = vertex; /* And it's parend is updated */
        /* We then proceed to the dfs step of the algorithm */
        searchArticulationPoints(G, adjVertex->v, discoveryTime, low,
                                 parent, visitTime, isArticulationPoint);

        if (low[vertex] > low[adjVertex->v])
        /* If the low value of the vertex is higher than the low value of
        one of his adjacent vertices, it is updated */
        low[vertex] = low[adjVertex->v];

        /* A vertex is an articulation point if:
        - It's not the root of a dfs tree and it's
        discoveryTime is less or equal to the low value of his adjacent vertices */
        if (low[adjVertex->v] >= discoveryTime[vertex] && parent[vertex] != NIL
            && isArticulationPoint[vertex] == FALSE) {

            isArticulationPoint[vertex] = TRUE;
            apcount++;
            if(vertex < min || min == -1)
            min = vertex + 1;
            if(vertex > max)
            max = vertex + 1;
        }

        /* -It's the root of a dfs tree and has 2 or more children */
        else if (children > 1 && parent[vertex] == NIL
            && isArticulationPoint[vertex] == FALSE) {

            isArticulationPoint[vertex] = TRUE;
            apcount++;
            if(vertex < min || min == -1)
            min = vertex + 1;
            if(vertex > max)
            max = vertex + 1;
        }
    }
    /* If the adjacent vertex has already been discovered,
    it's low value is updated (if needed) */
    else if (adjVertex->v != parent[vertex]) {
        if (low[vertex] > discoveryTime[adjVertex->v])
        low[vertex] = discoveryTime[adjVertex->v];
    }

}

void GRAPHsearch(Graph G) {


    int visitTime = 0; /* The current time in a dfs search*/
    int numberOfVertices = G -> V; /* The number of vertices in the graph */
    int vertex; /* The current vertex*/

    /* Following is the declaration of 4 auxiliary vectors to store properties of
    vertices: */
    int discoveryTime[numberOfVertices]; /* The discovery time in a dfs */
    int low[numberOfVertices]; /* The low */
    int parent[numberOfVertices]; /* The parent of the vertex in a dfs */
    int isArticulationPoint[numberOfVertices]; /* If the vertex is an articulation
    point */

    /* Firt we initialize the discovery time, parents, and articulation point
    property of each vertex */
    for (vertex = 0; vertex < numberOfVertices; vertex++) {
        discoveryTime[vertex] = NIL;
        parent[vertex] = NIL;
        isArticulationPoint[vertex] = FALSE;
    }

    /* We then proceed to do recursive depth search of the graph, starting in
    vertex 0 */
    for (vertex = 0; vertex < G->V; vertex++)
    if (discoveryTime[vertex] == NIL)
    searchArticulationPoints(G, vertex, discoveryTime, low,
                             parent, visitTime, isArticulationPoint);
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
    printf("%d %d\n", min, max);

    return 0;
}
