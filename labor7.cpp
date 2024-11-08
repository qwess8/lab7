// labor7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <malloc.h>
#include <random>
#include <time.h>

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

	DFS(vis, G, nG);

	getchar();
	getchar();
	return 0;
}

