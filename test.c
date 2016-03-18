#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int v, e, u, w, mode;
    mode = atoi(argv[1]);
    scanf("%d %d\n", &v, &e);

    if (mode == 1) { //duplicate full graph

        printf("%d %d\n", v*2, e*2+1);
        for (; e>0; e--) {
            scanf("%d %d\n", &u, &w);
            printf("%d %d\n", u, w);
            printf("%d %d\n", u+v, w+v);
        }
        printf("1 %d\n", v+1);
    }

    else if (mode == 2) { //duplicate vertices, mantain edges

        printf("%d %d\n", v*2, e);
        for (; e>0; e--) {
            scanf("%d %d\n", &u, &w);
            printf("%d %d\n", u, w);
        }
    }

    else if (mode == 3) { //mantain vertices, duplicate edges

        printf("%d %d\n", v, e*2);
        for (; e>0; e--) {
            scanf("%d %d\n", &u, &w);
            printf("%d %d\n", u, w);
            printf("%d %d\n", rand() % v, rand() % v);
        }

    }

    else {
        printf("Invalid mode\n");
        return 1;
    }

    return 0;
}
