#include <malloc.h>
#include <string.h>
#include "EstruturaDeDados.h"

static TListaAluno *AlListaInternal;
static TListaUC *UcListaInternal;
static TListaInsc *InListaInternal;

// Metodos para ALUNOS
void AlAdd(int AlNum, char *AlNome, char *AlPais)
{// Adicionar aluno á lista
	TListaAluno *novo;
	novo = (TListaAluno*)malloc(sizeof(TListaAluno));
	if (novo != NULL)
	{
		novo->AlNum = AlNum;
		novo->AlNome = (char*)malloc(strlen(AlNome) + 1);
		strcpy(novo->AlNome, AlNome);
		novo->AlPais = (char*)malloc(strlen(AlPais) + 1);
		strcpy(novo->AlPais, AlPais);

		novo->AlNext = AlListaInternal;
		AlListaInternal=novo;
		return;
	}
	return;
}
void AlInit()
{// Só para haver alguns alunos preenchidos
	AlAdd(111, "Pedro Duque", "PT");
	AlAdd(222, "Mario Constantino", "PT");
	AlAdd(333, "JoaoPereira", "PT");
	return;
}
void AlMostra(TListaAluno *AlLista)
{
	printf("\n ----- Alunos -----\n");
	printf("Numero:\t Pais:\t Nome:\n");
	while (AlLista != NULL)
	{
		printf("%d\t %s\t %s\n", AlLista->AlNum, AlLista->AlPais, AlLista->AlNome);
		AlLista = AlLista->AlNext;
	}
	return;
}
TListaAluno* GetListaAluno()
{
	return AlListaInternal;
}
// Fim dos metodos ALUNOS

// Metodos para Unidade Curricular
void UcAdd(int UcNum, char * UcNome, int UcAno, int UcSemestre, int UcECTS, int UcEstado)
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
		UCnovo->UcECTS = UcECTS;
		UCnovo->UcEstado = UcEstado;

		UCnovo->UcNext = UcListaInternal;
		UcListaInternal = UCnovo;
		return;
	}
	return;
}
void UcInit()
{
	UcAdd(123, "Programacao", 1, 1, 6, 1);
	UcAdd(456, "Fisica", 1, 2, 6, 1);
	UcAdd(789, "Matematica", 2, 2, 6, 1);
}
void UcMostra(TListaUC * UcLista)
{
	printf("\n ----- Unidades Corriculares -----\n");
	printf("Numero:\t Ano:\t Sem.:\t ECT:\t Est.:\t Nome:\n");
	while (UcLista != NULL)
	{
		printf("%d\t %d\t %d\t %d\t %d\t %s\n", UcLista->UcNum, UcLista->UcAno, UcLista->UcSemestre,UcLista->UcECTS,UcLista->UcEstado,UcLista->UcNome);
		UcLista = UcLista->UcNext;
	}
	return;
}
TListaUC* GetListaUC()
{
	return UcListaInternal;
}
// Fim dos metodos Unidade Curricular

// Metodos para Inscrições
void InAdd(int InAluno, int InUC, int InAnoLetivo)
{
	TListaInsc *novo;
	novo = (TListaInsc*)malloc(sizeof(TListaInsc));
	if (novo != NULL)
	{
		novo->InAluno = InAluno;
		novo->InUC = InUC;
		novo->InAnoLetivo = InAnoLetivo;
		novo->InEstado = 1; // Coloca o estado como ativo

		novo->InNext = InListaInternal;
		InListaInternal = novo;
		return; 
	}
	return;
}
void InMostra(TListaInsc * InLista)
{
	printf("\n ----- Inscricoes -----\n");
	printf("Numero:\t UC:\t Ano:\t Estado:\n");
	while (InLista != NULL)
	{
		printf("%d\t %d\t %d\t %d\n", InLista->InAluno, InLista->InUC, InLista->InUC,InLista->InEstado);
		InLista = InLista->InNext;
	}
	return;
}
TListaInsc* GetListaIn()
{
	return InListaInternal;
}
void InEdit(int InAluno, int InUC, int InAnoLetivo, int NovoEstado)
{
	while (InListaInternal != NULL)
	{
		if (InListaInternal->InAluno == InAluno &&
						InListaInternal->InAnoLetivo == InAnoLetivo &&
						InListaInternal->InUC == InUC)
		{
			InListaInternal->InEstado = NovoEstado;
			return;
		}
		InListaInternal = InListaInternal->InNext;
	}
	return;
}
// Fim dos metodos Inscrições