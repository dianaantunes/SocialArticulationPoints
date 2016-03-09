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

link newLINK(int, link);
Edge newEDGE(int, int);
Graph GRAPHinit(int);
void GRAPHinsertE(Graph, Edge);
void GRAPHremoveE(Graph, Edge);
int GRAPHedges(Edge [], Graph G);
void GRAPHdestroy(Graph);
void GRAPHshow(Graph G);
