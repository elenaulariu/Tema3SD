#include "graph.h"
#include "queue.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    fin = fopen(argv[2], "rt");
    fout = fopen(argv[3], "wt");
    int nrfilme, i, j, k, nr = 0, ok, **film;
    char **Actor;
    char *numefilm = malloc(100 * sizeof(char)), *numeactor = malloc(100 * sizeof(char));
    fscanf(fin, "%d\n", &nrfilme);
    int nractori[nrfilme];
    film = calloc(nrfilme, sizeof(int *));
    Actor = calloc(100, sizeof(char *));
    for (i = 0; i < nrfilme; i++)
    {
        fgets(numefilm, 100, fin);
        fscanf(fin, "%d\n", &nractori[i]);
        film[i] = calloc(nractori[i], sizeof(int));
        Actor = realloc(Actor, (nractori[i] + nr) * sizeof(char *));
        // Citeste numele actorilor, le atribuie un indice, si verifica daca numele a mai fost citit anterior.
        for (j = 0; j < nractori[i]; j++)
        {
            ok = 0;
            fgets(numeactor, 100, fin);
            for (k = 0; k < nr; k++)
            {
                // Daca da, in vectorul de vectori, care contine indicii actorilor, se repeta indicele oferit anterior actorului.
                if (strcmp(numeactor, Actor[k]) == 0)
                {
                    film[i][j] = k;
                    ok = 1;
                }
            }
            // Daca nu, i se atribuie un indice nou, care e adaugat in vectorul de vectori, si se mareste numarul de actori(noduri).
            if (ok == 0)
            {
                Actor[nr] = malloc((strlen(numeactor) + 1) * sizeof(char));
                strcpy(Actor[nr], numeactor);
                film[i][j] = nr;
                nr = nr + 1;
            }
        }
    }
    free(numeactor);
    free(numefilm);
    Film *filme = initFilm(nr);
    // Se creaza muchii intre noduri.
    for (i = 0; i < nrfilme; i++)
    {
        for (j = 0; j < nractori[i]; j++)
        {
            for (k = j + 1; k < nractori[i]; k++)
            {
                addEdge(filme, film[i][j], film[i][k]);
            }
        }
    }
    for (i = 0; i < nrfilme; i++)
    {
        free(film[i]);
    }
    free(film);
    // Se rezolva prima cerinta.
    if (strcmp(argv[1], "-c1") == 0)
    {
        int n = 0, *visited = calloc(filme->nr_actori, sizeof(int));
        int indice = biggestproduction(filme);
        int *v = calloc(filme->nr_actori, sizeof(int));
        int nr_con = bfs_iterative(filme, indice, visited, v);
        int temp;
        // Se aranjeaza in ordine crescatoarele actorii.
        for (i = 0; i < nr_con; i++)
        {
            for (j = i + 1; j < nr_con; j++)
            {
                if (strcmp(Actor[v[i]], Actor[v[j]]) > 0)
                {
                    temp = v[i];
                    v[i] = v[j];
                    v[j] = temp;
                }
            }
        }
        fprintf(fout, "%d\n", nr_con);
        for (i = 0; i < nr_con; i++)
        {
            fprintf(fout, "%s", Actor[v[i]]);
        }
        free(visited);
        free(v);
    }
    // Se rezolva cea de-a doua cerinta.
    if (strcmp(argv[1], "-c2") == 0)
    {
        // Se citesc numele celor doi actori, si sunt cautati printre actorii din graf.
        char *actor1 = malloc(100 * sizeof(char)), *actor2 = malloc(100 * sizeof(char));
        fgets(actor1, 100, fin);
        fgets(actor2, 100, fin);
        int index1, index2;
        for (i = 0; i < nr; i++)
        {
            if (strcmp(actor1, Actor[i]) == 0)
                index1 = i;
            if (strcmp(actor2, Actor[i]) == 0)
                index2 = i;
        }
        int level = grade(filme, index1, index2);
        fprintf(fout, "%d\n", level);
        free(actor2);
        free(actor1);
    }
    // Se rezolva cea de-a treia cerinta.
    if (strcmp(argv[1], "-c3") == 0)
    {
        int **punte, i, j, n, temp;
        punte = malloc(2 * filme->nr_actori * sizeof(int *));
        for (i = 0; i < filme->nr_actori; i++)
        {
            punte[i] = malloc(2 * sizeof(int));
        }
        n = punti(filme, punte);
        for (i = 0; i < filme->nr_actori; i++)
        {
            Actor[i][strlen(Actor[i]) - 1] = '\0';
        }
        // Sorteaza in ordine alfabetica cei doi actori care formeaza o punte.
        for (i = 0; i < n; i++)
        {
            if (strcmp(Actor[punte[i][0]], Actor[punte[i][1]]) > 0)
            {
                temp = punte[i][0];
                punte[i][0] = punte[i][1];
                punte[i][1] = temp;
            }
        }
        // Sorteaza in ordine alfabetica puntile.
        for (i = 0; i < n; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (strcmp(Actor[punte[i][0]], Actor[punte[j][0]]) > 0)
                {
                    temp = punte[i][0];
                    punte[i][0] = punte[j][0];
                    punte[j][0] = temp;
                    temp = punte[i][1];
                    punte[i][1] = punte[j][1];
                    punte[j][1] = temp;
                }
                if (strcmp(Actor[punte[i][0]], Actor[punte[j][0]]) == 0)
                {
                    if (strcmp(Actor[punte[i][1]], Actor[punte[j][1]]) > 0)
                    {
                        temp = punte[i][1];
                        punte[i][1] = punte[j][1];
                        punte[j][1] = temp;
                    }
                }
            }
        }
        fprintf(fout, "%d\n", n);
        for (i = 0; i < n; i++)
        {
            fprintf(fout, "%s %s\n", Actor[punte[i][0]], Actor[punte[i][1]]);
        }
        for (i = 0; i < filme->nr_actori; i++)
            free(punte[i]);
        free(punte);
    }
    for (i = 0; i < nr; i++)
    {
        free(Actor[i]);
    }
    free(Actor);
    destroy_graph(filme);
    fclose(fin);
    fclose(fout);
}