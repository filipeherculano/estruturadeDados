/**********************************************************************************************
*	This code was made by students from UECE - Universidade Estadual do Ceará - Brazil
*
*	This code is for a semester conclusion. The lecture was 'Data Structures' and this
* project focuses on the structure of a binary tree. And this code is also open source, to 
* help some students on difficult tasks like producing a code with this teory.
*
*	@autor - Filipe Herculano Rocha
***********************************************************************************************/

struct pessoa{
	int rg;
	int telefone;
	char *email;
	char *nome;
	struct pessoa *esq;
	struct pessoa *dir;
};

typedef struct pessoa *Pessoa;

Pessoa cadastrarNumero(Pessoa P, Pessoa root, int isFirst){
	if(isFirst) {
		printf("Raiz cadastrada com sucesso.\n");
		return P;
	} else {
		if(P->telefone < root->telefone){
			if(root->esq == NULL){
				printf("Cadastro feito com sucesso!\n");
				root->esq = P;
				return NULL;
			} else cadastrarNumero(P, root->esq, isFirst); 
		} else if(P->telefone > root->telefone){
			if(root->dir == NULL){
				printf("Cadastro feito com sucesso!\n");
				root->dir = P;
				return NULL;
			} else cadastrarNumero(P, root->dir, isFirst);
		} else printf("Número já cadastrado, por favor, digite outro.\n");
	} 
	return NULL;
}

Pessoa removerNumero(Pessoa root, Pessoa P, Pessoa auxRoot){
	if(auxRoot->telefone == P->telefone) {
		char c;
		do{
			printf("Nome : %s", P->nome);
			printf("Email: %s", P->email);
			printf("RG: %d\n\n", P->rg);
			printf("Pessoa achada, deseja realmente removê-la? <s> sim ou <n> não.\n");
			scanf("%c", &c);
			if(c == 's') printf("Pessoa eliminada!\n");
			else if(c == 'n'){
				printf("Processo cancelado.\n");
				return NULL;
			} else printf("Letra errada. Digite s ou n!\n");
		}while(c != 's' && c != 'n');
		Pessoa auxEsq = auxRoot->esq;
		Pessoa auxDir = auxRoot->dir;
		auxRoot = auxDir;
		free(auxDir);
		cadastrarNumero(auxEsq, auxRoot, 0);
		return auxRoot;
	} else if(auxRoot->esq->telefone == P->telefone){
		char c;
		do{
			printf("Nome : %s", P->nome);
			printf("Email: %s", P->email);
			printf("RG: %d\n\n", P->rg);
			printf("Pessoa achada, deseja realmente removê-la? <s> sim ou <n> não.\n");
			scanf("%c", &c);
			if(c == 's') printf("Pessoa eliminada!\n");
			else if(c == 'n'){
				printf("Processo cancelado.\n");
				return NULL;
			} else printf("Letra errada. Digite s ou n!\n");
		}while(c != 's' && c != 'n');
		Pessoa auxEsq = auxRoot->esq;
		auxRoot->esq = NULL;
		cadastrarNumero(auxEsq->esq, root, 0);
		cadastrarNumero(auxEsq->dir, root, 0);
		return NULL;
 	} else if(auxRoot->dir->telefone == P->telefone){
		char c;
		do{
			printf("Pessoa achada: \n");
			printf("Nome : %s", P->nome);
			printf("Email: %s", P->email);
			printf("RG: %d\n\n", P->rg);
			printf("Deseja realmente removê-la? <s> sim ou <n> não.\n");
			scanf("%c", &c);
			if(c == 's') printf("Pessoa eliminada!\n");
			else if(c == 'n'){
				printf("Processo cancelado.\n");
				return NULL;
			} else printf("Letra errada. Digite s ou n!\n");
		}while(c != 's' && c != 'n');
		Pessoa auxDir = auxRoot->dir;
		auxRoot->dir = NULL;
		cadastrarNumero(auxDir->esq, root, 0);
		cadastrarNumero(auxDir->dir, root, 0);
		return NULL;
 	}
	else if(P->telefone < root->telefone) removerNumero(root, P, auxRoot->esq); 
	else if(P->telefone > root->telefone) removerNumero(root, P, auxRoot->dir);
}

Pessoa search(Pessoa root, int telefone){
	if(root == NULL) return NULL;
	else{
		if(root->telefone == telefone) return root;
		else if(telefone < root->telefone) search(root->esq ,telefone);
		else if(telefone > root->telefone) search(root->dir, telefone);
	}
}

void searchPreOrder(Pessoa root){
	if(root == NULL) return;

	printf("Telefone: %d\n", root->telefone);
	printf("Nome : %s", root->nome);
	printf("Email: %s", root->email);
	printf("RG: %d\n\n", root->rg);
	searchPreOrder(root->esq);
	searchPreOrder(root->dir);
}

void searchInOrder(Pessoa root){
	if(root == NULL) return;

	searchInOrder(root->esq);
	printf("Telefone: %d\n", root->telefone);
	printf("Nome : %s", root->nome);
	printf("Email: %s", root->email);
	printf("RG: %d\n\n", root->rg);
	searchInOrder(root->dir);
}

void searchPosOrder(Pessoa root){
	if(root == NULL) return;

	searchPosOrder(root->esq);
	searchPosOrder(root->dir);
	printf("Telefone: %d\n", root->telefone);
	printf("Nome : %s", root->nome);
	printf("Email: %s", root->email);
	printf("RG: %d\n\n", root->rg);
}