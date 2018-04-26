#include <stdio.h>
#include "EstruturaDeDados.h"

void main()
{
	TListaAluno *AlLista = NULL;
	TListaUC *UcLista = NULL;
	TListaInsc *InLista = NULL;

	AlLista = AlInit(AlLista);
	AlMostra(AlLista);

	UcLista = UcInit(UcLista);
	UcMostra(UcLista);

	InLista = InAdd(InLista, 111, 123, 2017);
	InLista = InAdd(InLista, 222, 456, 2017);
	InLista = InAdd(InLista, 333, 789, 2017);
	InMostra(InLista);

	printf("Hellow Horld\n");
	return;
}