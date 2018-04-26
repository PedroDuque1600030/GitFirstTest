#include <stdio.h>
#include "UserInterface.h"
#include "SistemaControlo.h"
#include "EstruturaDeDados.h"


int main()
{
	
	/*TListaAluno *Al=NULL;
	TListaUC *UC=NULL;
	TListaInsc *In=NULL;*/

	// Chamar a inicialização com alguns alunos e UCs
	Init(); 

	// aqui é que se inicia o verdadeiro programa
	UiStart();

//	ImprimirListagem(ListagemUCmenos5Alunos(2017));
	

	/*Al = GetListaAluno();
	UC = GetListaUC();
	while (UC != NULL)
	{
		printf("Alunos na UC %d - %s, são: %d\n",UC->UcNum ,UC->UcNome, CountAlunosUC(UC->UcNum, 2017));
		UC = UC->UcNext;
	}
*/
	return 1;
}
