#include <malloc.h>
#include <string.h>
#include "EstruturaDeDados.h"

extern TListaAluno *AlLista;

TListaAluno* AlAdd(TListaAluno *AlLista, int AlNum, char *AlNome, char *AlPais)
{
	TListaAluno *novo;
	novo = (TListaAluno*)malloc(sizeof(TListaAluno));
	if (novo != NULL)
	{
		novo->AlNum = AlNum;
		novo->AlNome = (char*)malloc(strlen(AlNome) + 1);
		strcpy(novo->AlNome, AlNome);
		novo->AlPais = (char*)malloc(strlen(AlPais) + 1);
		strcpy(novo->AlPais, AlPais);

		novo->AlNext = AlLista;
		return novo;
	}
	return AlLista;
}

TListaAluno* AlInit(TListaAluno *AlLista)
{
	AlLista = AlAdd(AlLista, 111, "Pedro Duque", "PT");
	AlLista = AlAdd(AlLista, 222, "Mario Constantino", "PT");
	AlLista = AlAdd(AlLista, 333, "JoaoPereira", "PT");
	return AlLista;
}
void AlMostra(TListaAluno *AlLista)
{
	printf("Numero:\t Pais:\t Nome:\n");
	while (AlLista != NULL)
	{
		printf("%d\t %s\t %s\n", AlLista->AlNum, AlLista->AlPais, AlLista->AlNome);
		AlLista = AlLista->AlNext;
	}
	return;
}