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

/********************************************************************************
*	Uma estrutura é criada com todas as informações inerentes à cada indivíduo.
*	Assim como um typedef para referenciar um ponteiro para a estrutura, facili-
*	tando assim a passagem de parâmetros.
*********************************************************************************/
struct pessoa{
	int rg;
	int telefone;
	char *email;
	char *nome;
	struct pessoa *esq;
	struct pessoa *dir;
};

typedef struct pessoa *Pessoa;

/***********************************************************************************
*	Parâmetros: Ponteiro para a estrutura que será adicionada = P
*				Ponteiro para a estrutura raiz mais ancestral da árvore = root
*				Booleano para identificar quando retornar um NULL ou não = isFirst
*	Return:		Quando é o primeiro cadastro ele retorna o ponteiro que referencia
*				ele. Retorna NULL quando é outro além deste.
*
*	Se a variável booleana for verdadeira, é retornado o ponteiro para essa estru-
*	tura. Se não, é verificado se o valor telefone é menor ou maior que o valor 
*	no nó em questão. Se for maior ou menor e os ponteiros para os lados esquerdos
*	e direitos forem NULL (Podem ser alocadas novos cadastros), então é ligado o 
*	ponteiro *esq da strutura acima ao ponteiro que aponta para a nova estrutura 
*	retornando assim NULL. Se os valores menores ou maiores não forem NULL (Existe
*	um nó filho) é chamado o mesmo método cadastrarNumero() dando assim um caráter
*	recursivo. Essa nova chamada receberá os mesmos parâmetros, porém agora com
*	o parâmetro que antes era root, agora será uma das duas filhas. Se o valor 
*	telefone é igual ao do nó em questão, é printado ao usuário a informação de
*	que já existe e é retornado NULL.
***********************************************************************************/
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

/********************************************************************************************
	Parâmetros:	Ponteiro para estrutura à ser removida = P
				Ponteiro para raiz mais ancestral = root
				Ponteiro para raiz auxiliar que começa como root = auxRoot
	Return:		Se a estrutura removida for a raiz mais ancestral, então ao final
				será retornada a nova raiz mais ancestral. Se a estrutura removida
				for qualquer outra, será retornado NULL

	Este método também é recursivo em algumas condições, porém a primeira instância é
	verificado logo se a raiz mais ancestral ou uma de suas filhas é a estrutura à ser
	removida, se for este irá entrar em uma das 3 condições do início. Todas as 3 possuem
	o mesmo do-while que é relacionado com a condição de resposta Sim ou Não do usuário
	em relação à remoção ou não da estrutura. 

	Na primeira seção, é usado dois ponteiros auxiliares para as filhas do auxRoot atual 
	para que possamos cadastrar o ramo direito usando o ramo esquerdo (Escolha feita 
	aleatóriamente, não interfere na corretude) como nova raiz acenstral mais antiga. 
	Ao final, é usando cadastrarNumero() com novos parâmetros. É retornado assim a nova
	raiz ancestral.

	Na segunda seção, o telefone procurado é igual à filha esquerda da raiz. A ligação
	para a filha esquerda é anulada com NULL, é usado um ponteiro auxiliar para pegar 
	o endereço da filha esquerda na memória para poder manipulá-la. É usado agora a 
	função cadastrarNumero() duas vezes: uma para cadastrar a filha esquerda da filha
	esquerda da raiz que estávamos na raiz mais ancestral da árvore e uma para cadastrar
	a filha direita da filha esquerda que estávamos na raiz mais ancestral da árvore.
	Retorna-se NULL.

	Na terceira seção, é praticamente a mesma coisa da segunda. Sendo que agora será feito
	com o valor procurado do telefone sendo igual à filha direita da raiz que estamos.

	As duas últimas seções são a parte recursiva do método. Só são ativados, se a raiz atual
	não é igual ao valor telefone ou as filhas desta também não possuem esse número. Logo,
	é chamado removerNumero() novamente, sendo que agora com o terceiro parâmetro sendo a 
	filha esquerda ou direita da raiz atual. 

	A função continua até remover o dado telefone pois a verificação se existe ou não o 
	número procurado é feita antes de entrar neste método, usando search().
*******************************************************************************************/

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

/**********************************************************************************
	Parâmetros:	Recebe um ponteiro para a raiz mais acenstral da árvore = root
				Recebe o valor do Telefone que deverá ser procurado = telefone
	Return: 	Retorna NULL se chegou ao final sem encontrar o valor telefone
				Retorna o ponteiro root quando é encontrado.

	Esse método usa da recursividade para procurar por toda a àrvore binária.
	Visto que a árvore implementada possui o lado esquerdo com menores valóres
	que o lado direito, se a raiz atual do método não tiver o valor do telefone
	ele irá descer para o lado esquerdo se for menor e para o lado direito se for
	maior. Cada uma das duas chama a função search() novamente. O método irá parar
	somente quando achar o valor ou quando chegar ao fim da procura sem resultados.
************************************************************************************/

Pessoa search(Pessoa root, int telefone){
	if(root == NULL) return NULL;
	else{
		if(root->telefone == telefone) return root;
		else if(telefone < root->telefone) search(root->esq ,telefone);
		else if(telefone > root->telefone) search(root->dir, telefone);
	}
}

// 		Recebe ponteiro root e printa na tela no estilo pré-ordem.
void searchPreOrder(Pessoa root){
	if(root == NULL) return;

	printf("Telefone: %d\n", root->telefone);
	printf("Nome : %s", root->nome);
	printf("Email: %s", root->email);
	printf("RG: %d\n\n", root->rg);
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
	printf("RG: %d\n\n", root->rg);
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
	printf("RG: %d\n\n", root->rg);
}