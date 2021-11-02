#include "graph.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY 9999

// Initializeaza graful.
Film *initFilm(int nr_actori)
{
    Film *film = malloc(sizeof(Film));
    film->nr_actori = nr_actori;
    film->adjList = malloc(nr_actori * sizeof(Actor *));
    int i;
    for (i = 0; i < nr_actori; i++)
        film->adjList[i] = NULL;
    return film;
}

// Creaza un nod pentru actorul cu indexul indexActor.
Actor *createActor(int indexActor)
{
    Actor *newActor = malloc(sizeof(Actor));
    newActor->nrActor = indexActor;
    newActor->leg = NULL;
    return newActor;
}

// Adauga o muchie intre cele doua noduri.
void addEdge(Film *graph, int actor1, int actor2)
{
    Actor *newActor = createActor(actor2);
    newActor->leg = graph->adjList[actor1];
    graph->adjList[actor1] = newActor;
    newActor = createActor(actor1);
    newActor->leg = graph->adjList[actor2];
    graph->adjList[actor2] = newActor;
}

// Afla care este cea mai mare productie.
int biggestproduction(Film *graph)
{
    int i, *num_comp = calloc(graph->nr_actori, sizeof(int)), max = 0, indice, *index = calloc(graph->nr_actori, sizeof(int));
    int *visited, n;
    // Afla numarul de componente inrudite cu fiecare nod, si il compara cu numarul maxim.
    for (i = 0; i < graph->nr_actori; i++)
    {
        visited = calloc(graph->nr_actori, sizeof(int));
        n = bfs_iterative(graph, i, visited, index);
        num_comp[i] = n;
        if (num_comp[i] > max)
        {
            indice = i;
            max = num_comp[i];
        }
        free(visited);
    }
    free(num_comp);
    free(index);
    return indice;
}

// Parcurge toate nodurile inrudite cu nodul sursa, le numara, si le adauga intr-un vector. Returneaza numarul de noduri din productie.
int bfs_iterative(Film *graph, int source, int *visited, int *index)
{
    int x, i = 0;
    Queue *q = init_queue();
    Actor *temp;
    visited[source] = 1;
    enqueue(q, source);
    while (queue_size(q) != 0)
    {
        x = front(q);
        index[i] = x;
        i++;
        dequeue(q);
        temp = graph->adjList[x];
        while (temp != NULL)
        {
            if (visited[temp->nrActor] == 0)
            {
                visited[temp->nrActor] = 1;
                enqueue(q, temp->nrActor);
            }
            temp = temp->leg;
        }
    }
    free(q);
    return i;
}

// Afla care este gradul de inrudire dintre nodul sursa si nodul destinatie.
int grade(Film *graph, int source, int destination)
{
    int x, i = 0, d;
    Queue *q = init_queue();
    Actor *temp;
    int *visited = calloc(graph->nr_actori, sizeof(int)), *distance = calloc(graph->nr_actori, sizeof(int));
    visited[source] = 1;
    distance[destination] = -1;
    enqueue(q, source);
    while (queue_size(q) != 0)
    {
        x = front(q);
        dequeue(q);
        temp = graph->adjList[x];
        while (temp != NULL)
        {
            if (visited[temp->nrActor] == 0)
            {
                visited[temp->nrActor] = 1;
                distance[temp->nrActor] = distance[x] + 1;
                enqueue(q, temp->nrActor);
            }
            temp = temp->leg;
        }
    }
    d = distance[destination];
    free(q);
    free(visited);
    free(distance);
    return d;
}

// Afla toate puntiile unui graf si le trece intr-o matrice. Returneaza numarul de punti.
int punti(Film *graph, int **punti)
{
    int i, j = 0, k = 0, timp = 0, idx[graph->nr_actori], low[graph->nr_actori], parent[graph->nr_actori];
    for (i = 0; i < graph->nr_actori; i++)
    {
        idx[i] = -1;
        low[i] = INFINITY;
        parent[i] = 0;
    }
    // Afla puntiile pentru fiecare nod.
    for (i = 0; i < graph->nr_actori; i++)
    {
        if (idx[i] == -1)
        {
            j = 0;
            int *punte = malloc(graph->nr_actori * graph->nr_actori * sizeof(int)), n = 0;
            dfsB(graph, i, &timp, idx, low, parent, punte, &n);
            while (j < n)
            {
                punti[k][0] = punte[j];
                j++;
                punti[k][1] = punte[j];
                j++;
                k++;
            }
            free(punte);
        }
    }
    return k;
}

// Afla daca exista punti intre nodul sursa si nodurile inrudite cu acesta, parcurgand graful in adancime.
void dfsB(Film *graph, int source, int *timp, int *idx, int *low, int *parent, int *punte, int *n)
{
    int i = 0;
    idx[source] = (*timp);
    low[source] = (*timp);
    (*timp)++;
    Actor *temp = graph->adjList[source];
    while (temp != NULL)
    {
        if (temp->nrActor != parent[source])
        {
            if (idx[temp->nrActor] == -1)
            {
                parent[temp->nrActor] = source;
                dfsB(graph, temp->nrActor, timp, idx, low, parent, punte, n);
                if (low[source] > low[temp->nrActor])
                    low[source] = low[temp->nrActor];
                if (low[temp->nrActor] > idx[source])
                {
                    punte[(*n)++] = source;
                    punte[(*n)++] = temp->nrActor;
                }
            }
            else if (low[source] > idx[temp->nrActor])
                low[source] = idx[temp->nrActor];
        }
        temp = temp->leg;
    }
}

// Goleste memoria grafului.
void destroy_graph(Film *graph)
{
    int i;
    Actor *temp, *p;
    for (i = 0; i < graph->nr_actori; i++)
    {
        temp = graph->adjList[i];
        while (temp != NULL)
        {
            p = temp;
            temp = temp->leg;
            free(p);
        }
    }
    free(graph->adjList);
    free(graph);
}