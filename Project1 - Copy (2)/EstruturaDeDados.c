#include <malloc.h>
#include <string.h>
#include "EstruturaDeDados.h"

//extern TListaAluno *AlLista;

// Metodos para ALUNOS
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
// Fim dos metodos ALUNOS

// Metodos para Unidade Curricular
TListaUC * UcAdd(TListaUC * UcLista, int UcNum, char * UcNome, int UcAno, int UcSemestre, int UcEstado)
{
	TListaUC *UCnovo;
	UCnovo = (TListaUC*)malloc(sizeof(TListaUC));
	if (UCnovo != NULL)
	{
		UCnovo->UcNum = UcNum;
		UCnovo->UcNome = (char*)malloc(strlen(UcNome) + 1);
		strcpy(UCnovo->UcNome, UcNome);
		UCnovo->UcAno = UcAno;
		UCnovo->UcSemestre = UcSemestre;
		UCnovo->UcEstado = UcEstado;

		UCnovo->UcNext = UcLista;
		return UCnovo;
	}
	return UcLista;
}
TListaUC * UcInit(TListaUC * UcLista)
{
	UcLista = UcAdd(UcLista, 123, "Programacao", 1, 1, 1);
	UcLista = UcAdd(UcLista, 456, "Fisica", 1, 2, 1);
	UcLista = UcAdd(UcLista, 789, "Matematica", 2, 2, 1);
	return UcLista;
}
void UcMostra(TListaUC * UcLista)
{
	printf("Numero:\t Ano:\t Sem.:\t Est.:\t Nome:\n");
	while (UcLista != NULL)
	{
		printf("%d\t %d\t %d\t %d\t %s\n", UcLista->UcNum, UcLista->UcAno, UcLista->UcSemestre,UcLista->UcEstado,UcLista->UcNome);
		UcLista = UcLista->UcNext;
	}
	return;
}

// Fim dos metodos Unidade Curricular