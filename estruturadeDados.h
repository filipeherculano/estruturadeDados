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

/**********************************************************************************
*	Glossário: 	Ancestral Mais Antigo = raiz no nível mais alto da árvore binária.
*				Raiz Atual = raiz na qual estamos considerando como root no momento 
*				   em questão, pode ser ou não o ancestral mais antigo.
*				Ramo Esquerdo = filha esquerda da raiz atual.
*				Ramo Direito = filha direita da raiz atual.
***********************************************************************************/

/********************************************************************************
*	Uma estrutura é criada com todas as informações inerentes à cada indivíduo.
*	Assim como um typedef para referenciar um ponteiro para a estrutura, facili-
*	tando assim a passagem de parâmetros.
*********************************************************************************/
struct pessoa{
	long long rg;
	int telefone;
	char *email;
	char *nome;
	struct pessoa *esq;
	struct pessoa *dir;
};

typedef struct pessoa *Pessoa;

/*************************************************************************************
*	Parâmetros: P = Ponteiro para a estrutura que será adicionada
*				root = Ponteiro para a estrutura raiz mais ancestral da árvore
*				isFirst = Booleano para identificar quando retornar um NULL ou não
*
*	Return:		Quando é o primeiro cadastro ele retorna o ponteiro que referencia
*				ele. Retorna NULL quando é outro além deste.
*
*	Na função abaixo, existe dois tipos de retorno: Pessoa e NULL.
*
*	Quando ele retorna uma Pessoa, quer dizer que ele cadastrou o primeiro usuário 
*	da árvore. Porém, para isso ele precisa referênciar o usuário mais ancestral no 
*	nosso código main(). Por esse motivo, ele retorna o ponteiro P para quem a chamou
*	e lá nós atribuímos ao novo root.
*
*	Quando ele retorna NULL, isso significa que ele cadastrou alguém que não é mais o 
*	ancestral mais antigo da árvore binária. Porém, antes de cadastrar precisamos saber 
*	se o o novo nó possui um valor menor ou maior que o valor contido na raiz atual. 
*	Depois disso, verificamos se o ramo esquerdo ou direito aponta para NULL, se apontar
*	só é preciso alocar o novo nó neste ramo. Se não for NULL, é usado a mesma função 
*	de cadastrarNumero(), porém agora com um novo valor para a raiz atual, dependendo 
*	de qual lado que ele for.
***************************************************************************************/
Pessoa cadastrarNumero(Pessoa P, Pessoa root, int isFirst){
	if(P == NULL) return NULL;

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

/***********************************************************************************************
*	Parâmetros:	P = Ponteiro para estrutura à ser removida
*				root = Ponteiro para raiz mais ancestral
*				auxRoot = Ponteiro para raiz auxiliar que começa como root
*	Return:		Se a estrutura removida for a raiz mais ancestral, então ao final
*				será retornada a nova raiz mais ancestral. Se a estrutura removida
*				for qualquer outra, será retornado NULL
*
*	Neste método, também são retornados duas coisas: Pessoa ou NULL.
*
*	A Pessoa auxRoot começa sendo o mesmo de root, sendo que ao longo do método é ele quem 
*	vai ser usado para iterar novos valores de raiz e a Pessoa root vai ser sempre a raiz mais 
*	ancestral, só mudando quando esta é removida.
*
*	É retornado Pessoa quando o nó removido é o ancestral mais antigo. Neste caso, é usado dois 
*	auxiliares para pegar tanto o ramo esquerdo como direito do raiz atual. Escolhi que o ramo 
*	direito vai ser sempre o ramo que vai se tornar a raiz mais ancestral, poderia ter sido o 
*	esquerdo. Após a referenciação dos ramos, é usado um aux para pegar a nova raiz mais ancestral
*	(por convenção é a direita) e chamamos o método cadastrarNumero() usando o ramo esquerdo 
*	pegue anteriormente e inserido no ramo direito, agora chamado de auxRoot.
*
*	Caso a remoção não seja no ancestral mais antigo, haverá as opções de que o lado esquerdo ou o
*	lado direito sejam os valores procurados. Se forem, é usado um auxiliar para pegar o ramo em 
*	questão e após isso é iterado para que os ramos filhos do ramo que foi pegue sejam adicionados 
*	na raiz mais ancestral. Também usando cadastrarNumero(). A ligação para o ramo que foi removido
*	é anulada.
*
*	Em um último caso, se o valor continua sendo não encontrado, o valor auxRoot é atualizado se 
*	encaminhando para um dos lados: esquerdo ou direito.
*************************************************************************************************/

Pessoa removerNumero(Pessoa root, Pessoa P, Pessoa auxRoot){
	if(auxRoot->telefone == P->telefone) {
		char c;
		do{
			printf("Nome : %s", P->nome);
			printf("Email: %s", P->email);
			printf("RG: %lld\n\n", P->rg);
			printf("Pessoa achada, deseja realmente removê-la? <s> sim ou <n> não.\n");
			scanf("%c%*c", &c);
			if(c == 's') printf("Pessoa eliminada!\n");
			else if(c == 'n'){
				printf("Processo cancelado.\n");
				return NULL;
			} else printf("Letra errada. Digite s ou n!\n");
		}while(c != 's' && c != 'n');
		Pessoa auxEsq = auxRoot->esq;
		Pessoa auxDir = auxRoot->dir;
		auxRoot = auxDir;
		cadastrarNumero(auxEsq, auxRoot, 0);
		return auxRoot;
	} else if(auxRoot->esq->telefone == P->telefone){
		char c;
		do{
			printf("Nome : %s", P->nome);
			printf("Email: %s", P->email);
			printf("RG: %lld\n\n", P->rg);
			printf("Pessoa achada, deseja realmente removê-la? <s> sim ou <n> não.\n");
			scanf("%c%*c", &c);
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
			printf("RG: %lld\n\n", P->rg);
			printf("Deseja realmente removê-la? <s> sim ou <n> não.\n");
			scanf("%c%*c", &c);
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

/**********************************************************************************
*	Parâmetros:	Recebe um ponteiro para a raiz mais acenstral da árvore = root
*				Recebe o valor do Telefone que deverá ser procurado = telefone
*	Return: 	Retorna NULL se chegou ao final sem encontrar o valor telefone
*				Retorna o ponteiro root quando é encontrado.
*
*	Esse método usa da recursividade para procurar por toda a àrvore binária.
*	Visto que a árvore implementada possui o lado esquerdo com menores valóres
*	que o lado direito, se a raiz atual do método não tiver o valor do telefone
*	ele irá descer para o lado esquerdo se for menor e para o lado direito se for
*	maior. Cada uma das duas chama a função search() novamente. O método irá parar
*	somente quando achar o valor ou quando chegar ao fim da procura sem resultados.
************************************************************************************/

Pessoa search(Pessoa root, int telefone){
	if(root == NULL) return NULL;
	else{
		if(root->telefone == telefone) return root;
		else if(telefone < root->telefone) search(root->esq, telefone);
		else if(telefone > root->telefone) search(root->dir, telefone);
	}
}

// 		Recebe ponteiro root e printa na tela no estilo pré-ordem.
void searchPreOrder(Pessoa root){
	if(root == NULL) return;

	printf("Telefone: %d\n", root->telefone);
	printf("Nome : %s", root->nome);
	printf("Email: %s", root->email);
	printf("RG: %lld\n\n", root->rg);
	searchPreOrder(root->esq);
	searchPreOrder(root->dir);
}

// 		Recebe ponteiro root e printa na tela no estilo em ordem.
void searchInOrder(Pessoa root){
	if(root == NULL) return;

	searchInOrder(root->esq);
	printf("Telefone: %d\n", root->telefone);
	printf("Nome : %s", root->nome);
	printf("Email: %s", root->email);
	printf("RG: %lld\n\n", root->rg);
	searchInOrder(root->dir);
}

// 		Recebe ponteiro root e printa na tela no estilo pós-ordem.
void searchPosOrder(Pessoa root){
	if(root == NULL) return;

	searchPosOrder(root->esq);
	searchPosOrder(root->dir);
	printf("Telefone: %d\n", root->telefone);
	printf("Nome : %s", root->nome);
	printf("Email: %s", root->email);
	printf("RG: %lld\n\n", root->rg);
}

// Trata todas as entradas para cadastro.
int Exception(void *P, int exceptionNumber){
	switch(exceptionNumber){
		case 1:;
			long long aux = *(long long *)P;
			aux /= 10000000;
			if(aux >= 10 || !aux) {
				printf("\nNúmero tem que conter 8 dígitos.\n");
				return 0;
			} else if(aux != 3 && aux != 8 && aux != 9) {
				printf("\nNúmero não válido, por favor, iniciar com dígitos '3', '8' ou '9'\n");
				return 0;
			}
			break;
		case 2:;
			if(strlen(P) > 50) {
				printf("\nNome ou email precisam possuir no máximo 50 caracteres.\n");
				return 0;
			}
			break;
		case 3:
			aux = *(long long *)P;
			aux /= 100000000000000;
			if(aux >= 10) {
				printf("\nO RG não pode ter mais do que 15 dígitos.\n");
				return 0;
			}
			break;
	}
	return 1;
}