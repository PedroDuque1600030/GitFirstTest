#define ECTSPorUC 6
#include "SistemaControlo.h"
#include "EstruturaDeDados.h"
#include "string.h"
#include <malloc.h>

TListaAluno *GetAluno(int nrAluno)
{
    TListaAluno *a = GetListaAluno();

    while (a != NULL)
    {
        if (a->AlNum == nrAluno)
            return a;
        a = a->AlNext;
    }
    return NULL;
}

TListaUC *GetUC(int nrUC)
{
    TListaUC *a = GetListaUC();

    while (a != NULL)
    {
        if (a->UcNum == nrUC)
            return a;
        a = a->UcNext;
    }
    return NULL;
}

TListaInsc *GetInscricao(int nrAluno, int nrUC, int anoLetivo)
{
    TListaInsc *a = GetListaIn();

    while (a != NULL)
    {
        if (a->InAluno == nrAluno && a->InAnoLetivo == anoLetivo && a->InUC == nrUC && a->InEstado == 1)
            return a;

        a = a->InNext;
    }
    return NULL;
}

int GetPrimeiroAno(int nrAluno)
{
    int ano = 999999;
    TListaInsc *a = GetListaIn();

    while (a != NULL)
    {
        if (a->InAluno == nrAluno && a->InEstado == 1 && a->InAnoLetivo < ano)
            ano = a->InAnoLetivo;

        a = a->InNext;
    }
    return ano;
}

int GetNrECTS(int nrAluno, int anoLetivo)
{
    int ects = 0;

    TListaInsc *a = GetListaIn();
    
    while (a != NULL)
    {
        TListaUC *uc = GetUC(a->InUC);
        if (a->InAluno == nrAluno && a->InAnoLetivo == anoLetivo && a->InEstado == 1)
            ects += uc->UcECTS;

        a = a->InNext;
    }
    return ects;
}

int IsPortugues(int nrAluno)
{
    char *array[] = {"Portugal", "portugal", "PT", "pt", "Pt", "pT"};
    int i = 0;
    TListaAluno *al = GetAluno(nrAluno);

    for (i = 0; i < 6; i++)
    {
        if (strcmp(al->AlPais, array[i]) == 0)
            return 1;
    }

    return 0;
}

char *Inscrever(int nrAluno, int nrUC, int anoLetivo)
{
    int nrECTS;

    if (GetAluno(nrAluno) == NULL)
        return "Nao foi encontrado um aluno com este numero.";

    if (GetUC(nrUC) == NULL)
        return "Nao foi encontrada uma UC com este numero.";

    if (GetInscricao(nrAluno, nrUC, anoLetivo) != NULL)
        return "A inscricao ja existe para este aluno nesta cadeira e ano letivo.";

    nrECTS = GetNrECTS(nrAluno, anoLetivo);

    if (GetPrimeiroAno(nrAluno) == anoLetivo)
    {
        if (nrECTS + ECTSPorUC > 60)
            return "O aluno nao se pode inscrever a mais de 60 ECTS no primeiro ano.";
    }
    else if (nrECTS + ECTSPorUC > 84)
        return "O aluno nao se pode inscrever a mais que 84 ECTS no ano indicado.";

    InAdd(nrAluno, nrUC, anoLetivo);
    return "";
}

char *Anular(int nrAluno, int nrUC, int anoLetivo)
{
    TListaInsc *insc = GetInscricao(nrAluno, nrUC, anoLetivo);

    if (insc == NULL)
        return "A inscricao nao existe.";

    insc->InEstado = 0;
    return "";
}

char *CalcularPropinas(int nrAluno, int anoLetivo, float *resultado)
{
    float fator = 1;
    float valor = 0;
    int i = 0;

    if (GetAluno(nrAluno) == NULL)
        return "O aluno nao existe";

    if (!IsPortugues(nrAluno))
        fator = 1.2;

    if (GetPrimeiroAno(nrAluno) == anoLetivo)
        valor += 80 * fator;

    for (; i < GetNrECTS(nrAluno, anoLetivo); i++)
        valor += 15 * fator;

    *resultado = valor;
    return "";
}

void Gravar()
{
	printf("%s", GravaAlunosCSV());
	printf("%s", GravaUCsCSV());
	printf("%s", GravaInscricoesCSV());
}

void Ler()
{
	printf("%s", LerAlunosCSV());
	printf("%s", LerUCsCSV());
	printf("%s", LerInscCSV());
}

void Init()
{
    AlInit();
    UcInit();
}

TListagemInsc *ListagemAdd(TListagemInsc *atual, char *texto)
{
    TListagemInsc *novo;
    novo = (TListagemInsc *)malloc(sizeof(TListagemInsc));
    if (novo != NULL)
    {
        novo->Texto = (char *)malloc(strlen(texto) + 1);
        novo->Inner = NULL;
        strcpy(novo->Texto, texto);

        novo->Next = atual;
        return novo;
    }
    return NULL;
}

char* GetDescricaoEstado(TListaInsc* insc)
{
    return insc->InEstado == 1 ? "" : "(Anulada)";
}

TListagemInsc *ListagemPorUC()
{
    TListagemInsc *result = NULL;
    TListaUC *uc = GetListaUC();
    TListaInsc *insc = GetListaIn();
    int temInscricoes = 0;
    char str[100];

    while (uc != NULL)
    {
        sprintf(str, "UC numero %d", uc->UcNum);
        result = ListagemAdd(result, str);
        insc = GetListaIn();

        while (insc != NULL)
        {
            if (insc->InUC == uc->UcNum)
            {
                sprintf(str, "    Aluno numero %d em %d %s", insc->InAluno, insc->InAnoLetivo, GetDescricaoEstado(insc));
                result->Inner = ListagemAdd(result->Inner, str);
                temInscricoes = 1;
            }
            insc = insc->InNext;
        }

        if (temInscricoes == 0)
            result->Inner = ListagemAdd(NULL, "    Nao tem inscricoes");

        temInscricoes = 0;
        uc = uc->UcNext;
    }

    return result;
}

TListagemInsc *ListagemPorAluno()
{
    TListagemInsc *result = NULL;
    TListaAluno *aluno = GetListaAluno();
    TListaInsc *insc = GetListaIn();
    int temInscricoes = 0;
    char str[100];

    while (aluno != NULL)
    {
        sprintf(str, "Aluno numero %d - %s", aluno->AlNum, aluno->AlNome);
        result = ListagemAdd(result, str);
        insc = GetListaIn();

        while (insc != NULL)
        {
            if (insc->InAluno == aluno->AlNum)
            {
                sprintf(str, "    Inscrito na UC %d em %d %s", insc->InUC, insc->InAnoLetivo, GetDescricaoEstado(insc));
                result->Inner = ListagemAdd(result->Inner, str);
                temInscricoes = 1;
            }
            insc = insc->InNext;
        }

        if (temInscricoes == 0)
            result->Inner = ListagemAdd(NULL, "    Nao tem inscricoes");

        temInscricoes = 0;
        aluno = aluno->AlNext;
    }

    return result;
}
