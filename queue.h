#ifndef QUEUE_H_
#define QUEUE_H_

#ifndef NODE
#define NODE

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

#endif

typedef struct
{
    int size;
    Node *front, *back;
} Queue;

// Initializeaza o coada.
Queue *init_queue();

// Returneaza numarul de elemente din coada.
int queue_size(Queue *q);

// Adauga un element in coada.
void enqueue(Queue *q, int x);

// Sterge si dezaloca ultimul element din coada. (Intoarce 1 daca operatia a reusit si 0 in caz contrar)
int dequeue(Queue *q);

// Returneaza elementul din varful cozii.
int front(Queue *q);

#endif