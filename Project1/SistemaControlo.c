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
// retorna o nº de Alunos inscritos na numUC no anoLetivo
int CountAlunosUC(int numUC, int anoLetivo)
{
	TListaInsc *inscricoes = GetListaIn();
	// *insricoes apontador para a Lista de Inscrições.
	int cnt = 0;

	while (inscricoes != NULL)
	{
		// só incrementa se for inscrição não anulada, da numUC e do anoLetivo
		if (inscricoes->InUC == numUC && inscricoes->InEstado != 0 && inscricoes->InAnoLetivo == anoLetivo)
			cnt++;
		inscricoes = inscricoes->InNext;
	}
	return cnt;
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
    float valor = 0.0;
    int i = 0;

    if (GetAluno(nrAluno) == NULL)
        return "O aluno nao existe";

    if (!IsPortugues(nrAluno))
        fator = 1.2f;

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

void Init()
{ // a alpicação inicia aqui com a leitura dos ficheiros de dados
    LerAlunosCSV();
    LerUCsCSV();
    LerInscCSV();
}

TListagem *ListagemAdd(TListagem *atual, char *texto)
{
    TListagem *novo;
    novo = (TListagem *)malloc(sizeof(TListagem));
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

TListagem *ListagemPorUC()
{
    TListagem *result = NULL;
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

TListagem *ListagemPorAluno()
{
    TListagem *result = NULL;
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

TListagem* ListagemUCmenos5Alunos(int ano)
{ // listagem da opção 1) do eFolio-A 
	TListaUC* UC = GetListaUC();
	TListagem* item = NULL;
	int nAlunos = 0;
	char str[256];

	while (UC != NULL)
	{
		nAlunos = CountAlunosUC(UC->UcNum, ano);
		if (nAlunos <= 5)
		{
			if (nAlunos == 0)
				sprintf(str, "UC: %d - %s nao tem alunos inscritos no ano %d.", UC->UcNum, UC->UcNome, ano);
			if(nAlunos==1)
				sprintf(str, "UC: %d - %s tem: %d aluno inscrito no ano %d.", UC->UcNum, UC->UcNome, nAlunos,ano);
			if (nAlunos > 1)
				sprintf(str, "UC: %d - %s tem: %d alunos inscritos no ano %d.", UC->UcNum, UC->UcNome, nAlunos, ano);

			item = ListagemAdd(item, str);
		}
		UC = UC->UcNext;
	}
	return item;
}

TListagem* ListagemHorasPorAluno(int ano)
{
    TListaAluno* aluno = GetListaAluno();
    TListagem* item = NULL;
    int horasPorECTS = 26;
    char str[256];
    int nrECTS;
    
    while(aluno != NULL)
    {
        nrECTS = GetNrECTS(aluno->AlNum, ano);
        if (nrECTS > 0)
            sprintf(str, "Aluno numero %d - %s estima-se %d horas.", aluno->AlNum, aluno->AlNome, nrECTS * horasPorECTS);
        else 
            sprintf(str, "Aluno numero %d - %s nao tem inscricoes neste ano.", aluno->AlNum, aluno->AlNome);
        item = ListagemAdd(item, str);
        aluno = aluno->AlNext;
    }

    return item;
}

//  Obter listagem de alunos por país.

int jaListado(char* pais,char** lista_paises)
{
	int i =0;
	int result;
	int comp;

	while(lista_paises[i]!=NULL){
		
		comp = strcmp(pais,lista_paises[i]);
		if(comp ==0){
		result =0;
		return result;
		}		
		i++;
	}
	result =1;

	return result ;
}

int Countpaises(char* pais)
{
	TListaAluno *alunos = GetListaAluno();
	int cnt = 0;
    int comp;
	while (alunos != NULL)
	{
		comp = strcmp(pais,alunos->AlPais);		
		if (comp==0)
			cnt=cnt+1;
		alunos = alunos->AlNext;
	}
	return cnt;
}


TListagem* ListagemAlunosPorPais()
{
	int ret;
	int comp;
	int count;
    TListaAluno* aluno = GetListaAluno();
    TListagem* item = NULL;
    char str[256];
	char *lista_paises[256]={'\0'};
    int j=0;
	
    for(int i =0; aluno!= NULL;i++)
    {
		if(lista_paises[0]!='\0')
		{
		    comp=jaListado(aluno->AlPais,lista_paises); // verifica se país ja foi verificado
		}
		else {
			comp=1;
		}
		
		if(comp ==1) 
		{  //  nao está na lista
		
		    count=Countpaises(aluno->AlPais); // conta o numero de alunos que residem nesse pais
		
		    lista_paises[j]=aluno->AlPais; // Adiciona o país a lista dos verificados
			j++;
		
		    if(count>1){
		        sprintf(str, "- %d alunos residentes em %s",count, aluno->AlPais);
		    }
		    else {
		        sprintf(str, "- %d aluno residente em %s",count, aluno->AlPais);
		    }
      	  
            item = ListagemAdd(item, str);
            aluno = aluno->AlNext;
		}
		else // está na lista
		{
			aluno = aluno->AlNext;

	    }	
    }

    return item;
}
// Fim de obter listagem por pais
