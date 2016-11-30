//
//  main.c
//  foo
//
//  Created by Eduardo Pacheco on 30/11/16.
//  Copyright © 2016 Eduardo Pacheco. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char strA[50];
char strB[50];
int lenA, lenB;

int** mem_opt;	// memoiza a maior subsequencia para um de um ponto da strA apartir de um ponto da strB
				// acesso: mem_opt[A][B]

int opt_subsequence (int posA, int posB);

int main () {
	scanf ("%s %s", strA, strB);

	lenA = (int) strlen (strA);
	lenB = (int) strlen (strB);

	mem_opt = (int**) malloc (sizeof(int*) * lenA);
	for (int i = 0; i < lenA; ++i)
	{
		mem_opt[i] = malloc(sizeof(int) * lenB);
		memset(mem_opt[i], 0xFF, sizeof(int) * lenB); // seta tudo para -1
	}


	// X = <A, C, B, D, E, G, C, E, D, B, G> e Y = <B, E, G, C, F, E, U, B, K>
/*
ACBDEGCEDBG
BEGCFEUBK
*/
	printf ("%d\n", opt_subsequence (0, 0));

	int j = 0;
	for (int i = 0; i < lenA && j < lenB; ++i) {
		if ((i == lenA-1 && mem_opt[i][j] == 1) || mem_opt[i][j] != mem_opt[i+1][j])
		{
			printf("%c", strA[i]);

			char *aux = strchr (strB, strA[i]);
			if (aux != NULL)
				j = (int) (aux - strB) + 1;
			else
				j = lenB;
		}
	}

	printf("\n");

	return 0;
}

int opt_subsequence (int posA, int posB) {
	if (posA == lenA || posB == lenB)
		return 0;

	if (mem_opt[posA][posB] != -1)
		return mem_opt[posA][posB];

	int ret = opt_subsequence(posA + 1, posB); // nao adiciona posA

	char* aux = strchr (strB + posB, strA[posA]); // procure a primeira ocorrencia de A em B.
	if (aux != NULL)
	{
		//proximo caractere de A, a partir do ponto em comum com B
		int iaux = opt_subsequence(posA+1, (int)(aux - strB) + 1) + 1;

		if (iaux > ret)
			ret = iaux;
	}

	mem_opt[posA][posB] = ret;
	return ret;
}
