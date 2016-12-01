//
//  main.c
//  foo
//
//  Created by Eduardo Pacheco on 1/12/16.
//  Copyright © 2016 Eduardo Pacheco. All rights reserved.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool char
#define true 1
#define false 0

unsigned int *optmem[2];

int opt (char* str, int i, bool allowBig);

int main () {
	char *str;
	scanf("%s", str);

	int len = (int) strlen (str);

	optmem[0] = (unsigned int*) malloc(sizeof(unsigned int)*len);
	memset (optmem[0], 0xFF, sizeof(int)*len);
	optmem[1] = (unsigned int*) malloc(sizeof(unsigned int)*len);
	memset (optmem[1], 0xFF, sizeof(int)*len);

	printf("%d\n", opt (str, 0, true));

	int i;
	for (i = 0; i < len && optmem[true][i] < optmem[false][i]; ++i)
		printf("%c", toupper(str[i]));

	for (; i < len; ++i)
		printf("%c", tolower(str[i]));

	printf("\n");

	return 0;
}

int opt (char* str, int i, bool allowBig) {
	if (i == strlen(str))
		return 0;

	if (optmem[allowBig][i] != -1)
		return optmem[allowBig][i];

	if (allowBig)
	{
		int aux1 = opt (str, i + 1, true) + islower(str[i]); // se era minuscula, +1 (para ficar maiuscula)
		int aux2 = opt (str, i + 1, false) + isupper(str[i]); // se era maiuscula, +1 (para ficar minuscula)

		if (aux2 < aux1)
			aux1 = aux2;

		optmem[allowBig][i] = aux1;
	}
	else
		optmem[allowBig][i] = opt (str, i+1, false) + isupper (str[i]); // se era maiuscula, +1 (para ficar minuscula)

	return optmem[allowBig][i];
}
