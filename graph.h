#ifndef _GRAPH_H
#define _GRAPH_H

#include "queue.h"
#include <stdio.h>

typedef struct node
{
    int nrActor;
    struct node *leg;
} Actor;

typedef struct graph
{
    int nr_actori;
    Actor **adjList;
} Film;

// Initializeaza graful.
Film *initFilm(int nr_actori);

// Creaza un nod pentru actorul cu indexul indexActor.
Actor *createActor(int indexActor);

// Adauga o muchie intre cele doua noduri.
void addEdge(Film *film, int actor1, int actor2);

// Afla care este cea mai mare productie.
int biggestproduction(Film *graph);

// Parcurge toate nodurile inrudite cu nodul sursa.
int bfs_iterative(Film *graph, int source, int *visited, int *index);

// Afla care este gradul de inrudire dintre doua noduri.
int grade(Film *graph, int source, int destination);

// Afla toate puntiile unui graf.
int punti(Film *graph, int **punti);

// Afla daca exista punti intre nodul sursa si nodurile inrudite cu acesta.
void dfsB(Film *graph, int source, int *timp, int *idx, int *low, int *parent, int *punte, int *n);

// Goleste memoria grafului.
void destroy_graph(Film *graph);

#endif