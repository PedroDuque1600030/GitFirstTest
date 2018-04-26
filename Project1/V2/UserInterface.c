#include <stdlib.h>
#include <stdio.h>
#include "UserInterface.h"
#include "SistemaControlo.h"

void ImprimirListagem(TListagem *r)
{
	TListagem *i2 = NULL;

	while (r != NULL)
	{
		printf("%s\n", r->Texto);
		i2 = r->Inner;
		while (i2 != NULL)
		{
			printf("%s\n", i2->Texto);
			i2 = i2->Next;
		}

		r = r->Next;
	}
}

void UiStart()
{

	int selection;
	int nrAluno, nrUC, anoLetivo;
	char *message;
	float resultado = 0;

	while (1)
	{
		//system("cls");
		selection = -1;
		fflush(stdin);
		printf("**** Gestao de Matriculas ****\n");
		printf("\n1-Inscrever");
		printf("\n2-Anular");
		printf("\n3-Listagem de Inscricoes UC");
		printf("\n4-Listagem de Inscricoes Aluno");
		printf("\n5-Calcular Propinas");
		printf("\n6-Gravar");
		printf("\n7-Listagem de horas por aluno");
		printf("\n8-Listagem de UC com menos de 5 alunos");
		printf("\n0-Sair");
		printf("\nSelecione uma opcao: ");
		scanf("%d", &selection);
		system("cls");
		switch (selection)
		{

		case 1:

			printf("** Nova Inscricao **\n");
			printf("Introduza o numero de aluno:");
			scanf("%d", &nrAluno);
			printf("Introduza o numero da UC:");
			scanf("%d", &nrUC);
			printf("Introduza o ano letivo:");
			scanf("%d", &anoLetivo);

			printf("%s\n", Inscrever(nrAluno, nrUC, anoLetivo));

			break;

		case 2:
			printf("** Anular Inscricao **\n");
			printf("Introduza o numero de aluno:");
			scanf("%d", &nrAluno);
			printf("Introduza o numero da UC:");
			scanf("%d", &nrUC);
			printf("Introduza o ano letivo:");
			scanf("%d", &anoLetivo);

			printf("%s\n", Anular(nrAluno, nrUC, anoLetivo));
			break;

		case 3:
			printf("** Listagem de Inscricoes UC **\n");
			ImprimirListagem(ListagemPorUC());
			printf("\n ");
			break;

		case 4:
			printf("** Listagem de Inscricoes Aluno **\n");
			ImprimirListagem(ListagemPorAluno());
			printf("\n ");
			break;

		case 5:
			printf("** Calcular Propinas **\n");
			printf("Introduza o numero de aluno:");
			scanf("%d", &nrAluno);
			printf("Introduza o ano letivo:");
			scanf("%d", &anoLetivo);
			message = CalcularPropinas(nrAluno, anoLetivo, &resultado);
			printf("Valor das propinas do aluno num:%d para o ano de %d :%s %f\n", nrAluno, anoLetivo, message, resultado);

			break;

		case 6:
			printf("** Gravar **");
			printf("\n1-Gravar alterações");
			printf("\nOutra-Cancelar");
			printf("\n");
			scanf("%d", &selection);
			if (selection == 1)
			{
				Gravar();
			}
			break;
		case 7:
			printf("** Listagem de horas por aluno **\n");
			printf("\nIntroduza o ano:");
			scanf("%d", &anoLetivo);
			ImprimirListagem(ListagemHorasPorAluno(anoLetivo));
			printf("\n ");
			break;
		case 8:
			printf("** Listagem de UC com menos de 5 alunos **\n");
			printf("\nIntroduza o ano:");
			scanf("%d", &anoLetivo);
			ImprimirListagem(ListagemUCmenos5Alunos(anoLetivo));
			printf("\n ");
			break;
		case 0:
			printf("\nConfirmar saida?");
			printf("\n1-Sair");
			printf("\nOutra-Cancelar");
			printf("\n");
			scanf("%d", &selection);
			if (selection == 1)
			{
				exit(1);
			}
			break;
		default:
			printf("\nOpcao nao valida, escolha novamente\n");
			printf("\n");
		}
	}
}
