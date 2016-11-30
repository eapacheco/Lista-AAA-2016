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
int *mem_sel;   // memoizacao do melhor corte possivel a partir de tal posicao da string
char *mem_palindrome; // memoizacao da qualidade de palindromo entre as substring e acessado como matriz (coluna + largura*linha)
// mem_palindrome:	  A R A R A	onde x = -1; a matriz pode nao estar completa em tempo de execucao
//			A 1 0 1 0 1     	      os valores sao calculados conforme a necessidade
//			R x 1 0 1 0 
// 			A x x 1 0 1
// 			R x x x 1 0
// 			A x x x x 1

// retorna se uma substring de str (global) eh palindroma
char isPalyndrome (int a, int b);
// retorna o minimo de cortes possiveis para a string (local)
// eh chamada recursivamente para (str+1), ou seja a substring a partir da proxima letra
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

	// se a e b sao o mesmo caractere e a substring entre eles eh palindroma, essa substring tambem eh
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

	aux = str + i; // substring comecando na proxima letra igual aa primeira (onde pode haver uma palindroma)
	int j = i; // indice dessa proxima letra

	unsigned int min = -1; // unsigned -1 = maior valor possivel

	while ( aux != NULL && min > 0 ) // enquanto nao houver um corte imbativel (= 0), e nao acabaram as possiveis palindromas
	{				 // continue verificando
		if (isPalyndrome (i, j))
		{
			if (j == len - 1) // se ja chegou no fim da palavra, nao precisou cortar nada
				min = 0;
			else
				if ((ret = min_cuts(str, j+1)) + 1 < min)	// se retornou um valor inferior ao maximo
					min = ret + 1;				// mesmo com o corte extra, achou um corte melhor
		}

		aux = strchr (aux+1, *aux); // pega a proxima aparicao da letra => possivel palindromo
		j = (int) (aux - str);
	}

	mem_sel[i] = min;
	return min;
}
