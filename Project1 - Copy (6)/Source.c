#include <stdio.h>
#include "EstruturaDeDados.h"

void main()
{
	TListaAluno *AlLista = NULL;
	TListaUC *UcLista = NULL;
	TListaInsc *InLista = NULL;
	
	// exemplo acrescentar alunos e mostrar
	AlInit();
	AlLista = GetListaAluno();
	AlMostra(AlLista);

	// Exemplo acrescentar UC e mostrar
	UcInit();
	UcLista = GetListaUC();
	UcMostra(UcLista);


	// Exemplo Fazer algumas inscrições e mostrar
	InAdd(111, 123, 2017);
	InAdd(222, 456, 2017);
	InAdd(333, 789, 2017);
	InLista = GetListaIn();
	InMostra(InLista);
	// Exemplo alterar uma inscrição e mostrar
	InEdit(222,456,2017, 0); // Alterar estado de inscrição aluno 222
	InMostra(InLista);

	printf("Estado da gravacao:%d", Grava());

	return;
}