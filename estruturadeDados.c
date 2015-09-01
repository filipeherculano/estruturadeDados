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
#include <string.h>

// Incluindo biblioteca customizada a fim de deixar mais organizado!
#include "estruturadeDados.h"

/********************************************************************
*	Define tamanho máximo que vai ser lido pela função Getline()
*	para os arrays: nome e email.   						  
********************************************************************/
size_t STRING_SIZE = 52;

int main(){
	//	Aloca a memória e direciona o ponteiro "root".
	Pessoa root = NULL;
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
			// É tratado a excessão de quando o usuário entra com 
			// uma string ao invés de um inteiro com a função atoi()	
			char buffer[256];
			fgets(buffer, 256, stdin);
			option = atoi(buffer);
			switch(option){
				case 1:	;
					/**************************************************************************
					*	Nesta seção, aloca-se na memória o espaço para uma estrutura e é refe-
					*	rênciado "P". Em cada do-while é pedido uma informação para o usuário 
					*	de forma que só saia quando esta informação está de acordo com o proje-
					*	to:
					*
					*	Telefone: 8 dígitos começando em 3, 8 ou 9. Não existir nenhum outro 
					*	número cadastrado igual.
					*	
					*	Nome: No máximo 50 caracteres.
					*
					*	Email: No máximo 50 caracteres.
					*
					*	RG: no máximo 15 dígitos.
					*	
					*	Em todos os casos é chamado o método Exception() para se verificar tudos.
					*
					*	Ao final, é verificado se é o primeiro usuário da árvore quem está sendo 
					*	cadastrado. Se for, o ponteiro root vai receber a referência para este en-
					*	dereço na memória. Se não for, é só chamada o método cadastrarNumero().
					****************************************************************************/
					Pessoa P = malloc(sizeof(struct pessoa));
					do{
						printf("Digite seu número de telefone que NÃO ESTÁ CADASTRADO: \n");
						fgets(buffer, 256, stdin);
						P->telefone = atoi(buffer);
					}while(!Exception(&P->telefone, 1) || search(root, P->telefone) != NULL);

					printf("Número pode ser cadastrado, agora insira:\n");

					do{	
						printf("\t->Seu nome: \n");
						getline(&P->nome, &STRING_SIZE, stdin);
					}while(!Exception(P->nome, 2));

					do{
						printf("\t->Seu email: \n");
						getline(&P->email, &STRING_SIZE, stdin);
					}while(!Exception(P->email, 2));

					do{
						printf("\t->Seu RG: \n");
						fgets(buffer, 256, stdin);
						P->rg = atoll(buffer);
					}while(!Exception(&P->rg, 3));


					if(isFirst) {
						root = cadastrarNumero(P, root, isFirst);
						isFirst = 0;
					} else cadastrarNumero(P, root, isFirst);
					break;
				case 2: ;
					/***************************************************************************
					*	Aqui, será pedido ao usuário para que insira um número de telefone
					*	para ser pesquisado na estrutura. A função search() irá procurar
					*	na árvore binária o valor especificado. Se não for achado nenhum o
					*	ponteiro "P" receberá NULL. Se for achado, o ponteiro "P" receberá
					*	um ponteiro que aponta para o local na memória que contem o local
					*	item procurado. Após isso, o if-else decidirá qual informação retornar 
					*	ao usuário.
					*	(Olhar método search() e documentação deste na header estruturadeDados.h)
					***************************************************************************/
					int tel;
					printf("Insira o número para pesquisar.\n");
					fgets(buffer, 256, stdin);
					tel = atoi(buffer);
					P = search(root, tel);
					if(P != NULL) {
						printf("\n\t->Pessoa achada:\n");
						printf("Nome : %s", P->nome);
						printf("Email: %s", P->email);
						printf("RG: %lld\n", P->rg);
						printf("Telefone: %d\n\n", P->telefone);
					} else printf("\t->Pessoa não cadastrada!\n");
					break;
				case 3:
					/***************************************************************************
					*	O usuário insere um telefone que será removido da estrutura. A 
					*	condição if-else decidirá se determinado número se encontra na árvo-
					*	re. Se estiver presente, a função removerNumero() será chamada. A
					*	variável auxiliar do tipo Pessoa irá receber o valor de retorno da 
					*	função removerNumero() e logo após será verificado se é NULL ou não.
					*	A função removerNumero() retorna NULL se o nó removido na árvore não
					*	é a raiz mais ancestral possível, ou origem. Se a função removerNumero()
					*	remove o acenstral mais antigo, ela retorna um ponteiro para o NOVO
					*	ancestral mais antigo. Aqui usamos uma atribuição para o nosso root para
					*	atualizar este valor, pois foi removido o anterior.
					*	(Olhar método removerNumero() e documentação dele na header estruturadeDados.h)
					*****************************************************************************/
					printf("\nInsira um número para ser removido.\n");
					char b[256];
					fgets(b, 256, stdin);
					tel = atoi(b);
					if(search(root, tel) == NULL) printf("Pessoa não cadastrada!\n");
					else {
						Pessoa aux = removerNumero(root, search(root, tel),root);
						if(aux != NULL) root = aux;
					}
					break;
				case 4:;
					//	O usuário irá entrar com o tipo de percurso que ele quer observar.
					int op;
					printf("\nSelecione uma opção de listagem.\n");
					printf("<1> Percurso em pré-ordem.\n");
					printf("<2> Percurso em ordem simétrica.\n");
					printf("<3> Percurso em pós-ordem.\n\n");
					fgets(buffer, 256, stdin);
					op = atoi(buffer);
					if(root == NULL) printf("\nNão existe árvore!\n");;
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