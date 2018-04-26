#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "EstruturaDeDados.h"

static TListaAluno *AlListaInternal;
static TListaUC *UcListaInternal;
static TListaInsc *InListaInternal;


// Gravar para ficheiros CSV
char* GravaAlunosCSV()
{
	TListaAluno* tmpLista = GetListaAluno();
	FILE *f;
	f = fopen("saveAlunos.csv", "w");
	if (f != NULL)
	{
		while (tmpLista != NULL)
		{
			fprintf(f, "%d;%s;%s\n", tmpLista->AlNum, tmpLista->AlNome, tmpLista->AlPais);
			tmpLista = tmpLista->AlNext;
		}
		fclose(f);
	}
	else
		return "Erro ao gravar para o ficheiro saveAlunos.csv.\n";

	return "Sucesso ao gravar saveAlunos.csv.\n";
}
char* GravaUCsCSV()
{
	TListaUC* tmpLista=GetListaUC();
	FILE *	f;

	f = fopen("saveUCs.csv", "w");
	if (f != NULL)
	{
		while (tmpLista != NULL)
		{
			fprintf(f, "%d;%s;%d;%d;%d\n", tmpLista->UcNum, tmpLista->UcNome, tmpLista->UcAno, tmpLista->UcSemestre, tmpLista->UcECTS);
			tmpLista = tmpLista->UcNext;
		}
		fclose(f);
	}
	else
		return "Erro ao gravar para o ficheiro saveUCs.csv.\n";
	return "Sucesso ao gravar saveUCs.csv.\n";
}
char* GravaInscricoesCSV()
{
	TListaInsc* tmpLista = GetListaIn();
	FILE *	f;
	f = fopen("saveInscricoes.csv", "w");
	if (f != NULL)
	{
		while (tmpLista != NULL)
		{
			if (tmpLista->InEstado != 0) // só grava se não foi anulada
			fprintf(f, "%d;%d;%d\n", tmpLista->InAluno, tmpLista->InUC, tmpLista->InAnoLetivo);
			tmpLista = tmpLista->InNext;
		}
		fclose(f);
	}
	else 
		return "Erro ao gravar para o ficheiro saveInscricoes.csv.\n";
	
	return "Sucesso ao gravar saveInscricoes.csv.\n";
}

char* LerAlunosCSV()
{
	char str[999];
	FILE *f;
	char *tmp;
	int numAl;
	char nomeAl[255];
	char paisAl[100];

	f = fopen("saveAlunos.csv", "r");
	if (f != NULL)
	{
		while (fgets(str, 65535, f) != NULL)
		{
			tmp = strtok(str, ";");
			numAl = atoi(tmp);

			tmp = strtok(NULL, ";");
			strcpy(nomeAl, tmp);

			tmp = strtok(NULL, ";\n");
			strcpy(paisAl, tmp);

			AlAdd(numAl, nomeAl, paisAl);
		}
		fclose(f);
	}
	else
		return "Erro ao ler o ficheiro saveAlunos.csv.\n";
	return "Ficheiro saveAlunos.csv lido com sucesso.\n";
}
char* LerUCsCSV()
{
	char str[999];
	FILE *f;
	char *tmp;
	int numUC,anoUC,semestreUC,ectsUC;
	char nomeUC[255];

	f = fopen("saveUCs.csv", "r");
	if (f != NULL)
	{
		while (fgets(str, 65535, f) != NULL)
		{
			tmp = strtok(str, ";");
			numUC = atoi(tmp);

			tmp = strtok(NULL, ";");
			strcpy(nomeUC, tmp);

			tmp = strtok(NULL, ";\n");
			anoUC = atoi(tmp);

			tmp = strtok(NULL, ";\n");
			semestreUC=atoi(tmp);

			tmp = strtok(NULL, ";\n");
			ectsUC = atoi(tmp);

			UcAdd(numUC,nomeUC,anoUC,semestreUC,ectsUC,1);
		}
		fclose(f);
	}
	else
		return "Erro ao ler o ficheiro saveUCs.csv.\n";
	return "Ficheiro saveUCs.csv lido com sucesso.\n";
}
char* LerInscCSV()
{
	char str[999];
	FILE *f;
	char *tmp;
	int numAl, numUC, AnoLec;

	f = fopen("saveInscricoes.csv", "r");
	if (f != NULL)
	{
		while (fgets(str, 65535, f) != NULL)
		{
			tmp = strtok(str, ";");
			numAl = atoi(tmp);

			tmp = strtok(NULL, ";");
			numUC = atoi(tmp);

			tmp = strtok(NULL, ";\n");
			AnoLec = atoi(tmp);

			InAdd(numAl,numUC, AnoLec);
		}
		fclose(f);
	}
	else
		return "Erro ao ler o ficheiro saveInscricoes.csv.\n";
	return "Ficheiro saveInscricoes.csv lido com sucesso.\n";
}


// Metodos para ALUNOS
void AlAdd(int AlNum, char *AlNome, char *AlPais)
{// Adicionar aluno � lista
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
{// S� para haver alguns alunos preenchidos
	AlAdd(111, "Pedro Duque", "PT");
	AlAdd(222, "Mario Constantino", "PT");
	AlAdd(333, "JoaoPereira", "PT");
	AlAdd(444, "Teste", "EN");
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
	UcAdd(754, "LabProg", 2, 2, 6, 1);
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

// Metodos para Inscri��es
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
// Fim dos metodos Inscri��es
