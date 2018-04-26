#pragma once
#ifndef EstruturaH
#define EstruturaH

#include <stdio.h>

// Lista para ALUNO
typedef struct SAluno
{
	int AlNum;
	char *AlNome;
	char *AlPais;
	struct SAluno *AlNext;
}TListaAluno;

// Lista para Unidade Curricular
typedef struct SUC
{
	int UcNum;
	char *UcNome;
	int UcAno;
	int UcSemestre;
	int UcEstado;
	struct SUC *UcNext;
}TListaUC;

// Lista para Inscrições
typedef struct SInsc
{
	int InAluno;
	int InUC;
	int InAnoLetivo;
	struct SInsc *InNext;
}TListaInsc;

// Metodos para ALUNOS
TListaAluno* AlAdd(TListaAluno *AlLista, int AlNum, char *AlNome, char *AlPais);
TListaAluno* AlInit(TListaAluno *AlLista);
void AlMostra(TListaAluno *AlLista);
// Fim dos metodos ALUNOS

// Metodos para Unidade Curricular
TListaUC* UcAdd(TListaUC *UcLista,int UcNum,char *UcNome,int UcAno,int UcSemestre,int UcEstado);
TListaUC* UcInit(TListaUC *UcLista);
void UcMostra(TListaUC *UcLista);
// Fim dos metodos Unidade Curricular
#endif // Header EstruturaH