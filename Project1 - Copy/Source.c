#include <stdio.h>
#include "EstruturaDeDados.h"

void main()
{
	TListaAluno *AlLista = NULL;
	TListaUC *UcLista = NULL;
	TListaInsc *InLista = NULL;

	AlLista = AlInit(AlLista);
	AlMostra(AlLista);

	printf("Hellow Horld\n");
	return;
}