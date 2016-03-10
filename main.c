#include <stdlib.h>
#include <stdio.h>
/* GRAPH ADT */

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

/* Sedgwicks code */

static int apcount, min = -1, max = -1;

void apR(Graph G, int w, int d[], int low[], int pre[], int cnt, int ap[])
  { link t; int v, children = 0;
    d[w] = cnt++; low[w] = d[w];
    for (t = G->adj[w]; t != NULL; t = t->next)
      if (d[v = t->v] == -1) {
          children++;
          pre[v] = w;
          apR(G, v, d, low, pre, cnt, ap);
          if (low[w] > low[v]) low[w] = low[v];
          if (low[v] >= d[w] && pre[w] != -1 && ap[w] == 0) {
            ap[w] = 1;
            apcount++;
            if(w < min || min == -1) min = w + 1;
            if(w > max) max = w + 1;
          }
          if (children > 1 && pre[w] == -1 && ap[w] == 0) {
            ap[w] = 1;
            apcount++;
            if(w < min || min == -1) min = w + 1;
            if(w > max) max = w + 1;
          }
      }
      else if (v != pre[w]) {
        if (low[w] > d[v]) low[w] = d[v];
      }

  }

void GRAPHsearch(Graph G)
  {
    int cnt, d[G -> V], low[G -> V], pre[G -> V];
    int ap[G -> V];
    int v;
    cnt = 0;
    for (v = 0; v < G->V; v++) {
      d[v] = -1;
      pre[v] = -1;
      ap[v] = 0;
    }
    for (v = 0; v < G->V; v++)
      if (d[v] == -1)
        apR(G, v, d, low, pre, cnt, ap);
  }

/* MAIN FILE */

int main() {

	int v, e, u; /*v = N; e = L*/
	scanf("%d %d", &v, &e);
	Graph network = GRAPHinit(v);
	for (; e>0; e--) {
		scanf("%d %d", &u, &v);
		Edge edge = newEDGE(u, v);
		GRAPHinsertE(network, edge);
	}

	/* ALGORITMOOOOOOOOO*/


  GRAPHsearch(network);
  printf("%d\n", apcount);
  printf("%d %d\n", min, max);

  return 0;
}


/*


void Tarjan(Graph g){

	int v = g->V;
	int d[u] = MAX_INT, low[v];
	int visited = 0;
	Stack stack = STACKinit();
	for (; u > 0; u--){
		if (d[u] == MAX_INT)
			TarjanVisit(u);
	}
	void TarjanVisit(int u){
		link t;
		int value;
		d[u] = visited;
		low[u] = visited++;
		STACKpush(stack, u);
		for (t = G -> adj[u]; t != NULL; t = t -> next){
			value = t -> v;
			if (d[value] || STACKin(stack, value)){
				if (d[value] == MAX_INT)
					TarjanVisit(value);
				low[u] = min(low[u], low[value])
				if (d[u] =
			}
		}

	}
}

*/
