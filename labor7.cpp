// labor7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <malloc.h>
#include <random>
#include <time.h>


typedef struct node {
    int n;
    struct node* next;
} node;

node** createAdj(int** G, int n) {
    node** A = (node**)malloc(n * sizeof(node*));
    for (int i = 0; i < n; ++i) {
        A[i] = NULL;
        node* tail = NULL; 
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == 1) {
                node* newNode = (node*)malloc(sizeof(node));
                newNode->n = j;
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

void printAdj(node** A, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d: ", i);
        node* current = A[i];
        while (current != NULL) {
            printf("%d ", current->n);
            current = current->next;
        }
        printf("\n");
    }
    printf("\n");
}

void checkVisA(int s, int *vis, node** A, int size){
	vis[s] = 1;
	printf("%d ", s);
	node* current = A[s];
	while(current!= NULL){
		if(vis[current->n] == 0){
			checkVisA(current->n, vis, A, size);
		}
		current = current->next;
	}
}

void DFSA(int *vis, node** A, int size){
	for(int i = 0;i<size;i++){
		if(vis[i]==0){
			checkVisA(i, vis, A, size);
			printf("\n");
		}
	}
}

int **createG(int size){
	int **G;
	G = (int**)malloc(size * sizeof(int*));
	for(int i = 0; i < size; i++){
		G[i] = (int*)malloc(size*sizeof(int));
	}
	for(int i = 0; i < size; i++){
		for(int j = i; j < size; j++){
			G[i][j] = rand()%2;
			if(i==j) G[i][j] = 0;
			G[j][i] = G[i][j];
		}
	}
	return G;
}

void printG(int **G, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}



void checkVis(int s, int *vis, int** G, int size){
	vis[s] = 1;
	printf("%d ", s);
	for(int i = 0;i<size;i++){
		if(G[s][i] == 1 && vis[i] == 0){
			checkVis(i, vis, G, size);
		}
	}
}
void DFS(int *vis, int** G, int size){
	for(int i = 0;i<size;i++){
		if(vis[i]==0){
			checkVis(i, vis, G, size);
			printf("\n");
		}
	}
}

void checkVisNR(int s, int *vis, int** G, int size){
	int flag = 1;
	vis[s] = 1;
	printf("%d ", s);
	while(flag>0){
		for(int i = 0;i<size;i++){
			if(vis[i]==1){
				for(int j = 0;j<size;j++){
					if(G[i][j]==1 && vis[j]==0){
						vis[j] = 1;
						printf("%d ", j);
						flag++;
					}
				}
				flag--;
			}
		}
	}
}


void DFSNR(int *vis, int** G, int size){
	for(int i = 0;i<size;i++){
		if(vis[i]==0){
			checkVisNR(i, vis, G, size);
			printf("\n");
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int nG; 
	printf("nG1 =");
	scanf("%d", &nG);
	int *vis = (int*)malloc(sizeof(int) * nG);

	for(int i = 0;i<nG;i++){
		vis[i] = 0;
	}

	int **G = createG(nG);

	printG(G, nG);

	//node** A = createAdj(G, nG);

	//printAdj(A, nG);

	DFSNR(vis, G, nG);
	//DFS(vis, G, nG);

	getchar();
	getchar();
	return 0;
}

