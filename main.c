#include "GRAPH.h"

int main() {

  Graph g = GRAPHinit(4);

  Edge e1 = EDGE(1,2);
  Edge e2 = EDGE(1,3);
  Edge e3 = EDGE(1,0);

  GRAPHinsertE(g, e1);
  GRAPHinsertE(g, e2);
  GRAPHinsertE(g, e3);

  GRAPHshow(g);

  return 0;
}
