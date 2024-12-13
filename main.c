#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#pragma comment(linker, "/STACK:16777216")

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct stack {
    int* data;
    int top;
    int capacity;
} stack;

stack* createStack(int capacity) {
    stack* s = (stack*)malloc(sizeof(stack));
    s->data = (int*)malloc(capacity * sizeof(int));
    s->top = -1;
    s->capacity = capacity;
    return s;
}

void push(stack* s, int value) {
    if (s->top == s->capacity - 1) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++s->top] = value;
}

int pop(stack* s) {
    if (s->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[s->top--];
}

int isEmpty(stack* s) {
    return s->top == -1;
}

node** createAdj(int** G, int size) {
    node** A = (node**)malloc(size * sizeof(node*));
    for (int i = 0; i < size; ++i) {
        A[i] = NULL;
        node* tail = NULL;
        for (int j = 0; j < size; ++j) {
            if (G[i][j] == 1) {
                node* newNode = (node*)malloc(sizeof(node));
                newNode->data = j;
                newNode->next = NULL;
                if (tail == NULL) {
                    A[i] = newNode;
                }
                else {
                    tail->next = newNode;
                }
                tail = newNode;
            }
        }
    }
    return A;
}

void printAdj(node** A, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d: ", i);
        node* current = A[i];
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}


int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; ++i) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            G[i][j] = rand() % 2;
            G[j][i] = (i == j) ? 0 : G[i][j];
        }
    }
    return G;
}

void printG(int** G, int size) {
    printf("  ");
    for (int i = 0; i < size; ++i) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < size; ++i) {
        printf("%d ", i);
        for (int j = 0; j < size; ++j) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void DFS(int** G, int size, int* vis, int s) {
    vis[s] = 1;
    printf("%d ", s);
    for (int i = 0; i < size; ++i) {
        if (G[s][i] == 1 && vis[i] == 0) {
            DFS(G, size, vis, i);
        }
    }
}
void check_vis(int** G, int size, int* vis, int s) {
    DFS(G, size, vis, s);
    for (int i = 0; i < size; ++i) {
        if (vis[i]==0) {
            DFS(G, size, vis, i);
            printf("\n");
        }
    }
}

void DFSA(node** A, int* vis, int s) {
    vis[s] = 1;
    printf("%d ", s);
    node* current = A[s];
    while (current != NULL) {
        if (vis[current->data] == 0) {
            DFSA(A, vis, current->data);
        }
        current = current->next;
    }
}

void DFSNR(int** G, int size, int* vis, int s) {
    stack* st = createStack(size);
    push(st, s);
    vis[s] = 1;
    printf("%d ", s);

    while (!isEmpty(st)) {
        int v = st->data[st->top];
        int found = 0;

        for (int i = 0; i < size; ++i) {
            if (G[v][i] == 1 && vis[i] == 0) {
                push(st, i);
                vis[i] = 1;
                printf("%d ", i);
                found = 1;
                break;
            }
        }

        if (!found) {
            pop(st);
        }
    }

    free(st->data);
    free(st);
}
void check_visNR(int** G, int size, int* vis, int s) {
    DFSNR(G, size, vis, s);
    for (int i = 0; i < size; ++i) {
        if (vis[i] == 0) {
            DFSNR(G, size, vis, i);
            printf("\n");
        }
    }
}

void check_visA(node** A, int size, int* vis, int s) {
    DFSA(A, vis, s);
    for (int i = 0; i < size; ++i) {
        if (vis[i] == 0) {
            DFSA(A, vis, i);
            printf("\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    int n = 10000;
    int s = 0;

    int* vis = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) vis[i] = 0;
    printf("Введите количество вершин: ");
    //scanf("%d", &n);
    printf("\n");

    int** M1 = createG(n);
    printf("Граф G1\n");
    //printG(M1, n);
    printf("Введите вершину входа: ");
    scanf("%d", &s);
    check_vis(M1, n, vis, s);
    printf("\nAdj\n");

    //node** A1 = createAdj(M1, n);
    //printf("Список смежности графа G1\n");
    //printAdj(A1, n);
    //for (int i = 0; i < n; ++i) vis[i] = 0;
    //check_visA(A1, n, vis, s);
    //for (int i = 0; i < n; ++i) vis[i] = 0;
    //printf("\nNR\n");

    //check_visNR(M1, n, vis, s);

    free(M1);
    //free(A1);
    free(vis);
}