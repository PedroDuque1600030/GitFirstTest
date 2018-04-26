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
	int UcECTS;
	int UcEstado; //não solicitado no enunciado, mas poderá fazer sentido se a UC for anulada
	struct SUC *UcNext;
}TListaUC;

// Lista para Inscrições
typedef struct SInsc
{
	int InAluno;
	int InUC;
	int InAnoLetivo;
	int InEstado;
	struct SInsc *InNext;
}TListaInsc;

// Metodos para ALUNOS
void AlAdd(int AlNum, char *AlNome, char *AlPais);
void AlInit(); 
void AlMostra(TListaAluno *AlLista);
TListaAluno* GetListaAluno();
// Fim dos metodos ALUNOS

// Metodos para Unidade Curricular
void UcAdd(int UcNum,char *UcNome,int UcAno,int UcSemestre,int UcECTS, int UcEstado);
void UcInit();
void UcMostra(TListaUC *UcLista);
TListaUC* GetListaUC();
// Fim dos metodos Unidade Curricular

// Metodos para Inscrições
void InAdd( int InAluno, int InUC, int InAnoLetivo);
void InMostra(TListaInsc *InLista);
TListaInsc* GetListaIn();
void InEdit(int InAluno, int InUC, int InAnoLetivo, int NovoEstado);
// Fim dos metodos Inscrições

#endif // Header EstruturaH