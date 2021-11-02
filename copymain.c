#include "graph.h"
#include "queue.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fin, *fout;
    fin = fopen(argv[2], "rt");
    fout=fopen(argv[3], "wt");
    if(strcmp(argv[1], "-c1")==0) {
        int nrfilme, i, j, k, nr=0, ok, **film;
        char **Actor;
        char *numefilm=malloc(100*sizeof(char)), *numeactor=malloc(100*sizeof(char));
        fscanf(fin, "%d\n", &nrfilme);
        int nractori[nrfilme];
        film=calloc(nrfilme,sizeof(int*));
        Actor=calloc(100, sizeof(char*));
        for(i=0; i<nrfilme; i++) {
            fgets(numefilm, 100, fin);
            fscanf(fin, "%d\n", &nractori[i]);
            film[i]=calloc(nractori[i],sizeof(int));
            Actor=realloc(Actor, (nractori[i]+nr)*sizeof(char*));
            for(j=0; j<nractori[i]; j++) {
                ok=0;
                fgets(numeactor, 100, fin);
                for(k=0; k<nr; k++) {
                    if(strcmp(numeactor, Actor[k])==0) {
                        film[i][j]=k;
                        ok=1;
                    }
                }
                if(ok==0) {
                    Actor[nr]=malloc((strlen(numeactor)+1)*sizeof(char));
                    strcpy(Actor[nr], numeactor);
                    film[i][j]=nr;
                    nr=nr+1;
                }
            }
        }
        Film* filme=initFilm(nr);
        for(i=0; i<nrfilme; i++) {
            for(j=0; j<nractori[i]; j++) {
                fprintf(fout, "%d ", film[i][j]);
                for(k=j+1; k<nractori[i]; k++) {
                    if(existedge(filme, film[i][j], film[i][k])==0)
                        addEdge(filme, film[i][j], film[i][k]);
                }
                
            }
            fprintf(fout, "\n");
        }
        int source=biggestproduction(filme), n=0, *v=malloc(graph->nr_actori*sizeof(int));
        Queue *q=init_queue();
        enqueue(q, source);
        int *bfs_visited = calloc(filme->nr_actori, sizeof(int));
        bfs_recursive(filme, q, bfs_visited, v, &n);
        int nr_con=lengthofcon(filme, source);
        int *v=calloc(nr_con,sizeof(int));
        indici(filme, source, v);
        int temp;
        for(i=0; i<nr_con; i++) {
            for(j=i+1; j<nr_con; j++) {
                if(strcmp(Actor[v[i]], Actor[v[j]])>0) {
                    temp=v[i];
                    v[i]=v[j];
                    v[j]=temp;
                }
            }
        }
        printf("%d", source);
        fprintf(fout, "%d\n", nr_con);
        for(i=0; i<nr_con; i++) {
            //printf("%d\n", v[i]);
            fprintf(fout, "%s", Actor[v[i]]);
        }
        //destroy_graph(filme);
        //for(i=0; i<)
        
    }
}