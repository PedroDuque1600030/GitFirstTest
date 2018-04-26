#ifndef SistemaControlo
#define SistemaControlo
typedef struct SListagemInsc
{
	char *Texto;
    struct SListagemInsc *Inner;
	struct SListagemInsc *Next;
}TListagem;

/*
O método cria uma nova inscrição com os parâmetros dados. 
Fiquei na dúvida se devia utilizar int ou char* para o nrAluno e nrUC porque não sei se estes valores podem
ser alfanuméricos.

Nota PD:: Acho que devem ser int, na UAB são por isso vamos assumir que aqui tambem
    
Outra dúvida é em relação ao campo anoLetivo. Não é claro pelo enunciado o que isto significa, mas eu interpretei
como sendo o ano letivo em que o aluno está a inscrever-se. Por exemplo, vamos imaginar que este é o meu 3º ano na UAB.
Eu posso estar a inscrever-me numa UC do ano 1 mas o meu ano letivo será o 3º.

Nota PD: Estou de acordo vamos por como int

Algumas validações que eu vejo serem possíveis:
    1- O aluno existe
    2- A UC existe
    3- O aluno não se pode inscrever na mesma UC no mesmo ano letivo 2 vezes (a não ser que a inscrição existente esteja anulada)
    4- O aluno já não se pode inscrever a mais ECTS (máximo 60 no 1º ano e 84 nos seguintes)
    Nota PD: correponde ao que tenho na minha estrutura
*/
char* Inscrever(int nrAluno, int nrUC, int anoLetivo);
/*
Anula uma inscrição alterando o seu estado. 
Validar se:
    1- A inscrição existe para estes dados
    2- A inscrição não está anulada
    3- mais alguma??
*/
char* Anular(int nrAluno, int nrUC, int anoLetivo);

/*
Dado o nrAluno e o ano, é calculada a propina para esse ano letivo e colocada no parâmetro resultado. 
Ou seja, podemos obter daqui também um histórico de propinas do aluno chamando simplesmente este método para
anos letivos diferentes.
As validações são:
    1- O aluno não existe
    2- Não existem inscrições para o ano letivo dado
*/
char* CalcularPropinas(int nrAluno, int anoLetivo, float* resultado);

/*Este método simplesmente chama o método da BD. Para gravar os ficheiros dedados.*/
void Gravar();

TListagem* ListagemPorUC();

TListagem* ListagemPorAluno();

TListagem* ListagemUCmenos5Alunos(int ano);

TListagem* ListagemHorasPorAluno(int ano);

void Init();

#endif
