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

int n;
int v [50];
int* optmem;

int opt (int i, char onbuy);

int main () {
	int i;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
		scanf("%d", &v[i]);

	optmem = (int*) malloc(sizeof(int) * n * 2);
	memset(optmem, 0xFF, sizeof(int)*n*2);

	printf("%d\n", opt (0, 0));

	int j;
	for (int i = 0; i < n; i += 2) // mais dois para pular o dai da venda e do resfriamento
	{
		for (j = i; j < n && optmem[j + n] < optmem[j+1 + n]; ++j); // procura o dia da venda

		if (j == n) // nao houve mais vendas => nao houve mais compras
		{
			for (; i < n; ++i)
				printf("nada ");
		}
		else
		{
			int profit = optmem[i] - optmem[j];

			for (; i < j && (v[j] - v[i] != profit); ++i) // procura o dia da compra otima
				printf("nada ");

			printf("compra ");
			++i;

			for (; i < j; ++i)
				printf("nada ");
		}

		printf("venda resfriamento ");
	}

	printf("\n");

	return 0;
}

int opt (int i, char onbuy) {
	if (i >= n)
		return 0;

	if (optmem [i + onbuy*n] != -1)
		return optmem[i + onbuy*n];

	int ret, aux;

	if (!onbuy) // pode comprar
	{
		ret = opt (i + 1, 1) - v[i]; // compra
		aux = opt (i + 1, 0);		 // nao faz nada

		if (aux > ret)
			ret = aux;

		optmem[i + onbuy*n] = ret;
		return ret;
	}

	// tem que vender
	ret = opt (i + 2, 0) + v[i]; // vende, pula resfriamento
	aux = opt (i + 1, 1);		 // nao faz nada

	if (aux > ret)
		ret = aux;

	optmem [i + onbuy*n] = ret;
	return ret;
}
