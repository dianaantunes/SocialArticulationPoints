#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

    /* We declare an int v to store the number of people in the network (vertices)
    and reutilize to save one vertex of the edge, int u to store the other vertex
    of the edge and an int e to the number of connections between people (edges)*/
    int v, e, u, w; /*v = N; e = L*/
    v = atoi(argv[1]);
    e = atoi(argv[2]);
    /* First we read from stdin the number of vertices and edges to initialize the
    graf */
    
    /* We proceed to read all the connections from the input */
    printf("%d %d\n", v*3, e*3+2);
    for (; e>0; e--) {
        scanf("%d %d", &u, &w);
        printf("%d %d\n", u, w);
        printf("%d %d\n", u+v, w+v);
        printf("%d %d\n", u+2*v, w+2*v);

    }
    printf("1 %d\n", v+1); 
    printf("%d %d\n", v+1, 2*v+1); 

    return 0;
}