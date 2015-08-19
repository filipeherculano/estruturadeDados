/**********************************************************************************************
*	This code was made by students from UECE - Universidade Estadual do Ceará - Brazil
*
*	This code is for a semester conclusion. The lecture was 'Data Structures' and this
* project focuses on the structure of a binary tree. And this code is also open source, to 
* help some students on difficult tasks like producing a code with this teory.
*
*	@autor - Filipe Herculano Rocha
***********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "estruturadeDados.h"

size_t STRING_SIZE = 50;

int main(){
	Pessoa root = malloc(sizeof(struct pessoa));
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
					break;
				case 2: ;
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
					break;
				case 3:
					printf("Insira um número para ser removido.\n");
					scanf("%d%*c", &tel);
					if(search(root, tel) == NULL) printf("Pessoa não cadastrada!\n");
					else {
						Pessoa aux = removerNumero(root, search(root, tel),root);
						if(aux != NULL) root = aux;
					}
					break;
				case 4:;
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
