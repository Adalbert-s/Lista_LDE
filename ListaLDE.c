//Linear Duplamente Encadeada
//autor: Adalberto dos Santos Pinheiro
/*Objetivo: implementar uma lista duplamente encadeada para fins didaticos*/

#include<stdio.h>
#include<stdlib.h>

typedef struct no {

    int dado;
    struct no *ant;
    struct no *prox;        

} No;

typedef struct {

    No *inicio;
    No *fim;
    int tam;

} ListaLDE;

//funcoes de manipulacao

void cria(ListaLDE *l);
int insere(ListaLDE *l, int dado);
int retira(ListaLDE *l, int dado);

//funcoes de visualizacao

int estaVazia(ListaLDE l);
int getTamanho(ListaLDE l);
int mostra(ListaLDE);
int verifica(ListaLDE l, int dado);


int main(){

    ListaLDE l;
    int dado, sucesso, opcao;

    cria(&l);

/* INSERINDO ORDENADO */
    sucesso = insere(&l, 400); // eu optei por nao verificar se houve sucesso na insercao
    sucesso = insere(&l, 250);
    sucesso = insere(&l, 666);
    sucesso = insere(&l, 5000);
    sucesso = insere(&l, 10);

    if(!estaVazia(l)){ //exibindo a lista
        printf("\n-------------------------------------------------\n");
        mostra(l);
    }
    opcao = 1;
    while(opcao == 1){ // remover ate o usuario nao querer mais


        printf("\n-------------------------------------------------\n");
        printf("Qual dado deseja remover? ");
        scanf("%d", &dado);
        getchar();

        verifica(l, dado);
        sucesso = retira(&l, dado); // removo o elemento solicitado pelo usuario
        if(!sucesso)
            printf("FALHA EM REMOVER: %d\n\n", dado);
        else{
            printf("Removido com sucesso\n");
            mostra(l); // exibo a lista atualizada
        }
            
            if(!estaVazia(l)){
            printf("\nDeseja remover mais algum elemento? \n1 - sim \n2 - nao\n");
            scanf("%d", &opcao);
            getchar();
            }
            else
            return 0;
    }
return 0; 
}

void cria(ListaLDE *l){

    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
}

int insere(ListaLDE *l, int dado){

    // alocando no na memoria e checando se deu certo
    No *aux = (No *) malloc(sizeof(No));
    if(aux == NULL)
        return 0;

    // guardando o dado e incrementando o tamanho da lista
    aux->dado = dado;
    l->tam++;

    /* 1o caso: primeiro elemento */
    if(l->inicio == NULL){

        //todos apontam para o unico no existente
        l->inicio = aux;
        l->fim = aux;
        aux->ant = l->fim;
        aux->prox = l->inicio;

        return 1;
    }

    /* 2o caso: dado menor que o dado do inicio, insere no inicio */
    if(dado < l->inicio->dado){

        aux->prox = l->inicio; //prox do novo inicio aponta para antigo inicio
        l->inicio->ant = aux; // anterior do antigo inicio aponta para novo inicio
        l->inicio = aux; //l->inicio aponta para novo inicio

        return 1;
    }

    /* 3o caso: dado maior que o dado do fim, insere no fim */
    if(dado > l->fim->dado){

        aux->ant = l->fim; //ant do novo fim aponta para antigo fim
        l->fim->prox = aux; //prox do antigo fim aponta para novo fim
        l->fim = aux; //l->fim aponta para novo fim

        return 1;
    }

    /* 4o caso: insercao ordenada no meio */

    // inicializa-se dois nos no comeco da lista, que serao responsaveis por percorre-la
    No *anterior = l->inicio;
    No *atual = anterior->prox;

    while(dado > atual->dado){

        // percorro a lista ate achar a posicao certa
        anterior = atual;
        atual = atual->prox;
    }
    // insiro o no entre anterior e atual
    aux->ant = anterior; // ant do novo no aponta para anterior
    aux->prox = atual; // prox do novo no aponta para atual
    anterior->prox = aux; // prox do anterior aponta para o novo no
    atual->ant = aux; // ant do atual aponta para o novo no

    return 1;
}

int verifica(ListaLDE l, int dado){
    No *aux;

    aux = l.inicio;
    while(aux->prox != NULL){
        aux = aux->prox;
        if(dado == aux->dado){
            printf("Dado encontrado!\n");
            return 1;
        }
        if(aux->prox == NULL && aux->dado != dado)
        printf("Dado nao encontrado\n");
        return 0;          
    }
    return 0;
}

int retira(ListaLDE *l, int dado){

    No *aux ;

    if(l->inicio == NULL){
        printf("Lista vazia\n");
        return 0;
    }

    /* 1o caso: lista unitaria */
    if((dado == l->inicio->dado) && (l->inicio == l->fim)) {

        aux = l->inicio; // aux aponta para o no que vou remover
        l->inicio = NULL; //inicio aponta pra null
        l->fim = NULL; // fim aponta pra null
        free(aux); // libero a memoria
        printf("Dado unitario removido com sucesso.\n");
        l->tam--;

        return 1;
    }

    /* 2o caso: removendo primeiro elemento */
    if(dado == l->inicio->dado ) {

        aux = l->inicio; // aux aponta para o no que vou remover
        l->inicio = aux->prox; //inicio aponta para o novo inicio (o segundo elemento)
        free(aux); //libero memoria
        printf("Dado removido com sucesso..\n");
        l->tam--;

        return 1;
    }

    /* 3o caso: removendo ultimo elemento */
    else if(dado == l->fim->dado) {

        aux = l->fim; 
        l->fim = aux->ant;
        free(aux); //libero a memoria
        printf("Dado removido com sucesso.\n");
        l->tam--;

        return 1;
    }

    /* 4o caso: removendo um elemento no meio */
    aux = l->inicio->prox; // aux aponta para o segundo elemento
    //percorro a lista ate achar o elemento, ou chegar no fim
    while((dado != aux->dado) && (aux != l->fim))
    aux = aux->prox;
    if(aux == l->fim){ // se cheguei ao fim, nao encontrei o elemento
    printf("O elemento %d nao esta na lista.\n", dado);
    return 0;
    }
    //se encontrei o elemento, removo ele
    aux->prox->ant = aux->ant; // o anterior do proximo a aux aponta para o elemento anterior a aux
    aux->ant->prox = aux->prox; // o proximo do anterior a aux aponta para o proximo elemento em relacao a aux
    free(aux); //libero a memoria
    l->tam--;
    return 1;
}

int estaVazia(ListaLDE l){

    if(l.inicio == NULL)
        return 1;

    return 0;
}

int getTamanho(ListaLDE l){

    return l.tam;
}

int mostra(ListaLDE l){

    No *aux;

    if(l.inicio == NULL)// lista vazia, nao mostra nada
            printf("Lista vazia!\n\n");

 // lista possui elementos, mostra dependendo do sentido

        printf("\n-------------------------------------------------\n");
        printf("Mostrando Lista\n\n");
        // percorrendo do inicio ao fim

        aux = l.inicio;
            while(aux != NULL){
                printf("Dado: %d\n", aux->dado);
                aux = aux->prox;
            }

return 1;
}