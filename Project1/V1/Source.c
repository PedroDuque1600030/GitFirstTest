#include <stdio.h>
#include "UserInterface.h"
#include "SistemaControlo.h"
#include "EstruturaDeDados.h"
#include <string.h>

void main()
{
	//TListaAluno *AlLista = NULL;
	//TListaUC *UcLista = NULL;
	//TListaInsc *InLista = NULL;
	//
	//printf("%s", LerAlunosCSV());
	//AlLista = GetListaAluno();
	//AlMostra(AlLista);

	//printf("%s", LerUCsCSV());
	//UcLista = GetListaUC();
	//UcMostra(UcLista);

	//printf("%s", LerInscCSV());
	//InLista = GetListaIn();
	//InMostra(InLista);

	//// Chamar a inicialização com alguns alunos e UCs
	//Init(); 

	//// inscrever alguns alunos
	//Inscrever(333, 123, 2017);
	//Inscrever(333, 456, 2017);
	//Inscrever(333, 789, 2017);

	//Inscrever(111, 123, 2017);

	//Inscrever(222, 123, 2017);
	//Inscrever(222, 123, 2018);
	//Inscrever(222, 789, 2018);

//	Anular(222, 123, 2017);
//	Anular(222, 789, 2017);
	// Fim da inscrição automática de alguns alunos

	//printf("%s", GravaAlunosCSV());
	//printf("%s", GravaUCsCSV());
	//printf("%s", GravaInscricoesCSV());

	// aqui é que se inicia o verdadeiro programa
	UiStart();

	return;
}