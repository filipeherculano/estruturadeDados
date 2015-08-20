/**********************************************************************************************
*	This code was made by students from UECE - Universidade Estadual do Ceará - Brazil
*	
*	This code was a project for a semester's conclusion. The lecture was called 'Data 
*	Structures' and this project focuses on the structure of a binary tree. Also, this 
*	code is 'open source', in order to help some students on difficult tasks like 
*	producing a code with this theory. 
*
*	PLEASE, DO NOT USE IT FOR YOUR OWN PRIVILEGES! USE ONLY FOR STUDYING PURPOSES!
*
*	Enjoy it.
*		
*						Author - Filipe Herculano Rocha
***********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Incluindo biblioteca pessoal a fim de deixar mais organizado.
#include "estruturadeDados.h"

/********************************************************************
*	Define tamanho máximo que vai ser lido pela função Getline()
*	para os arrays: nome e email.   						  
********************************************************************/
size_t STRING_SIZE = 50;

int main(){
	//	Aloca a memória e direciona o ponteiro "root".
	Pessoa root = malloc(sizeof(struct pessoa));
	//	isFirst será usado como identificador booleano.
	int option, isFirst = 1;
	do{
		printf("____________________\n");
		printf("|  Menu principal. |\n");
		printf("|__________________|\n\n");
		printf("Selecione uma opção.\n");
		printf("<1> Cadastrar número.\n");
		printf("<2> Pesquisar número.\n");
		printf("<3> Remover número.\n");
		printf("<4> Listar número.\n");
		printf("<5> Sair.\n");
		
		do{		
			scanf("%d%*c", &option);
			switch(option){
				case 1:	;
					/************************************************************************
					*	Nesta seção, é alocada na memória um espaço para uma estrutura
					*	que vai ter o "P" como ponteiro para referenciá-la. Recebe-se 
					*	valores de nome, email e RG após receber um valor válido para 
					*	o número do telefone. Logo após, verifica-se se é a primeira 
					*	vez que é cadastrado uma pessoa, se for, este será referenciado
					*	pelo ponteiro "root" a partir de agora. Se não for o primeiro,
					*	a função cadastrarNumero() é chamada sem atribuir nada à ninguém
					*	pois ela retorna NULL se cadastrar uma pessoa qualquer além da
					*	raiz mais acenstral. Ao final, o ponteiro "P" é desalocado.
					*	(Olhar método cadastrarNumero() e documentação dele na header estruturadeDados.h)
					*************************************************************************/
					Pessoa P = malloc(sizeof(struct pessoa));
					do{
						printf("Digite seu número de telefone que NÃO ESTÁ CADASTRADO: \n");
						scanf("%d%*c", &P->telefone);
					}while(search(root, P->telefone) != NULL);
					printf("Número pode ser cadastrado, agora insira:\n");
					printf("\t->Seu nome: \n");
					getline(&P->nome, &STRING_SIZE, stdin);
					printf("\t->Seu email: \n");
					getline(&P->email, &STRING_SIZE, stdin);
					printf("\t->Seu RG: \n");
					scanf("%d%*c", &P->rg);
					if(isFirst) root = cadastrarNumero(P, root, isFirst);
 					else cadastrarNumero(P, root, isFirst);
					isFirst = 0;
					free(P);
					P = NULL;
					break;
				case 2: ;
					/***************************************************************************
					*	Aqui, será pedido ao usuário para que insira um número de telefone
					*	para ser pesquisado na estrutura. A função search() irá procurar
					*	na árvore binária o valor especificado, se não for achado nenhum o
					*	ponteiro "P" receberá NULL. Se for achado o ponteiro receberá o
					*	local para onde deverá apontar na memória. Após isso, o if-else 
					*	decidirá qual informação retornar ao usuário. Ao final, o ponteiro 
					*	"P" é desalocado.
					*	(Olhar método e search() documentação dele na header estruturadeDados.h)
					***************************************************************************/
					int tel;
					printf("Insira o número para pesquisar.\n");
					scanf("%d", &tel);
					P = search(root, tel);
					if(P != NULL) {
						printf("\t->Pessoa achada:\n");
						printf("Nome : %s", P->nome);
						printf("Email: %s", P->email);
						printf("RG: %d\n", P->rg);
						printf("Telefone: %d\n\n", P->telefone);
					} else printf("\t->Pessoa não cadastrada!\n");
					free(P);
					P = NULL;
					break;
				case 3:
					/***************************************************************************
					*	O usuário entrará com um telefone que será removido da estrutura. A 
					*	condição if-else decidirá se determinado número se encontra na árvo-
					*	re. Se estiver presente, a função removerNumero() será chamada. A
					*	variável auxiliar do tipo Pessoa irá receber o valor de retorno da 
					*	função removerNumero() e logo após será verificado se é NULL ou não.
					*	A função removerNumero() retorna NULL se o nó removido na árvore não
					*	é a raiz mais ancestral possível, ou origem. Se não for NULL, o pon-
					*	teiro "root" irá receber o aux, pois a raiz mais ancestral foi removi-
					*	da e precisa-se que o root do código no main seja atualizado.
					*	(Olhar método removerNumero() e documentação dele na header estruturadeDados.h)
					****************************************************************************/
					printf("Insira um número para ser removido.\n");
					scanf("%d%*c", &tel);
					if(search(root, tel) == NULL) printf("Pessoa não cadastrada!\n");
					else {
						Pessoa aux = removerNumero(root, search(root, tel),root);
						if(aux != NULL) root = aux;
					}
					break;
				case 4:;
					//	O usuário irá entrar com o tipo de percurso que ele quer observar.
					int op;
					printf("Selecione uma opção de listagem.\n");
					printf("<1> Percurso em pré-ordem.\n");
					printf("<2> Percurso em ordem simétrica.\n");
					printf("<3> Percurso em pós-ordem.\n");
					scanf("%d%*c", &op);
					switch(op){
						case 1:
							searchPreOrder(root);
							break;
						case 2:
							searchInOrder(root);
							break;
						case 3:
							searchPosOrder(root);
							break;
						default:
							printf("\nOpção não cadastrada! Por favor, tente novamente.\n");
					}

					break;
				case 5:
					printf("---------------Fim de execução!---------------\n");
					break;
				default:
					printf("\nOpção não cadastrada! Por favor, tente novamente.\n");
			}	
		}while(option > 5 || option < 1);
	}while(option != 5);
	return 0;
}
