#include "graph.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Film* initFilm(int nr_actori) {
    Film* film = malloc(sizeof(Film));
    film->nr_actori = nr_actori;
    film->adjList = malloc(nr_actori*sizeof(Actor*));
    int i;
    for(i=0; i<nr_actori; i++) 
       film->adjList[i]=NULL;
    return film;
}

Actor* createActor (int indexActor) {
    Actor* newActor = malloc(sizeof(Actor));
    newActor->nrActor=indexActor;
    newActor->leg=NULL;
    return newActor;
}

void addEdge(Film* graph, int actor1, int actor2) {
    Actor *newActor = createActor(actor2);
    newActor->leg=graph->adjList[actor1];
    graph->adjList[actor1]=newActor;
    newActor = createActor(actor1);
    newActor->leg=graph->adjList[actor2];
    graph->adjList[actor2]=newActor;
}

int cmp(const void* a, const void* b) {
    char* a1=(char*) a;
    char* b1=(char*) b;
    return strcmp(a1, b1);
}
int biggestproduction(Film *graph) {
    int i, *num_comp=calloc(graph->nr_actori, sizeof(int)), max=0, indice;
    for(i=0; i<graph->nr_actori; i++) {
       num_comp[i]=lengthofcon(graph, i);
       if(num_comp[i]>max) {
           indice=i;
           max=num_comp[i];
       } 
    }
    free(num_comp);
    return indice;
}

int lengthofcon(Film *graph, int i) {
    Actor *temp=graph->adjList[i];
    int con=1;
    while(temp!=NULL) {
        con++;
        temp=temp->leg;
    }
    return con;
}

void bfs_recursive(Film *graph, Queue *queue, int *visited, int *index, int* n) {
    if(queue_size(queue)==0) return;
    int source, i, length=0;
    source=front(queue);
    visited[source]=1;
    dequeue(queue);
    index[*n]=source;
    (*n)++;
    Actor *temp=graph->adjList[source];
    while(temp!=NULL)
     {  if(visited[temp->nrActor]==0) {
            visited[temp->nrActor]=1;
            push_back(queue, temp->nrActor);
        }
    }    
    bfs_recursive(graph, queue, visited, index, &n);
}

void indici(Film *graph, int source, int* v) {
    Actor *temp=graph->adjList[source];
    v[0]=source;
    int i=1;
    while(temp!=NULL) {
        v[i++]=temp->nrActor;
        temp=temp->leg;
    }
}
void printGraph(Film *graph, FILE *fout) {
    Actor* temp;
    {int i=0;
        fprintf(fout, "%d\n", i);
        temp=graph->adjList[i];
        while (temp!=NULL) {
            fprintf(fout, "%d\n", temp->nrActor);
            temp=temp->leg;
        }
        
    }
    fprintf(fout, "\n");
}
int existedge (Film *graph, int x, int y) {
    Actor *temp=graph->adjList[x];
    int ok=0;
    while(temp!=NULL) {
        if(temp->nrActor==y) 
            ok=1;
        temp=temp->leg;
    }
    return ok;
}
void destroy_graph(Film *graph) {
    int i;
    for(i=0; i<graph->nr_actori; i++) {
        Actor* temp;
        while(graph->adjList[i]!=NULL) {
            temp=graph->adjList[i];
            graph->adjList[i]=graph->adjList[i]->leg;
            free(temp);
        }
    }
    free(graph);
}
