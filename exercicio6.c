//
//  main.c
//  foo
//
//  Created by Eduardo Pacheco on 29/11/16.
//  Copyright © 2016 Eduardo Pacheco. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int len;
char str [50];
int *mem_sel;   // memoizacao do melhor corte possivel apartir dessa letra
char *mem_palindrome;

char isPalyndrome (int a, int b);
unsigned int min_cuts (char *str, int i);

int main () {
	int i;
	scanf ("%s", str);

	len = (int) strlen (str);

	mem_sel = (int*) malloc (sizeof(int) * len);
	memset (mem_sel, -1, sizeof(int) * len); // todo mundo = -1

	mem_palindrome = (char*) malloc (len*len);
	memset (mem_palindrome, -1, len*len); 	// todo mundo = -1
	for (i = 0; i < len*len; i += len + 1) 	// [a,a] = 1
		mem_palindrome[i] = 1;

	int ret = min_cuts (str, 0);
	printf("%d\n", ret);

	for (i = 1; i < len; ++i)
		if (mem_sel[i] == ret - 1)
		{
			printf("%d ", i);
			--ret;
		}


	free (mem_sel);
	free (mem_palindrome);
}

char isPalyndrome (int a, int b) {
	if (b <= a) // b: fim da substring, a: inico
		return 1;

	if (mem_palindrome[a + len*b] != (char) -1) // verifico se ja calcule a qualidade de palindromo para essa substring
		return mem_palindrome[a + len*b];

	return mem_palindrome[a + len*b] = (str[a] == str[b]) && isPalyndrome (a+1, b-1);
}

//ababbbabbababa
// 0 1234567 8 90123
// a babbbab b ababa
unsigned int min_cuts (char *str, int i) {
	if (mem_sel[i] != -1) // verifico se ja sei a melhor resposta para esse ponto
		return mem_sel[i];

	int ret;
	char *aux;

	aux = str + i;
	int j = i;

	unsigned int min = -1; // unsigned -1 = maior valor possivel

	while ( aux != NULL && min > 0 )
	{
		if (isPalyndrome (i, j))
		{
			if (j == len - 1)
				min = 0; // se vai ate o final da palavra nao ha cortes
			else
				if ((ret = min_cuts(str, j+1)) + 1 < min)	// se retornou um valor inferior ao maximo
					min = ret + 1;									// mesmo com o corte extra
		}

		aux = strchr (aux+1, *aux); // pega a proxima aparicao da letra => possivel palindromo
		j = (int) (aux - str);
	}

	mem_sel[i] = min;
	return min;
}
