#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"
#define MAX_INT 2147483647

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



  GRAPHshow(network);

  return 0;
}





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


