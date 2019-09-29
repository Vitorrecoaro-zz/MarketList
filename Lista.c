#include<stdio.h>
#include<stdlib.h>

typedef struct noLista{
    char nome[101];
    struct noLista *prox;
}No;

typedef struct ListaCircular{
    struct noLista *inicio;
    int tamanho;
}Lista;

Lista *crialista();
void valoreslista(Lista *l1);
void imprimearquivo(Lista *l1);
void liberalista(Lista *l1);
void limpararquivo();
void imprimelista(Lista *l1);

int main(){
    int op,nPessoas,i;
    char enter='s';
    Lista *l;

    printf("-x-x-x- Menu -x-x-x-\n\n1 - Criar lista.\n2 - Imprimir lista.\n3 - Criar arquivo com a lista.\n4 - Formatar arquivo.\n0 - Sair\n\nDigite a opcao:");
    scanf(" %d",&op);
    system("clear");
    enter = 's';
    while(op!=0){
        if(op==1){
            l = crialista();
            printf("Digite o valor de participantes da lista:\n");
            scanf(" %d",&nPessoas);
            for(i=0;i<nPessoas;i++){
                valoreslista(l);
            }
        }
        else if(op==2){
            imprimelista(l);    
        }
        else if(op==3){
            imprimearquivo(l);
        }
        else if(op==4){
            limpararquivo();
        }
        else {
            printf("Opcao invalida.\n");
        }
        printf("Pressione \"y\" para continuar.\n");
        scanf(" %c",&enter);
        while(enter!='y'){
            scanf(" %c",&enter);
        }
        enter = 's';
        system("clear");       
        printf("-x-x-x- Menu -x-x-x-\n\n1 - Criar lista.\n2 - Imprimir lista.\n3 - Criar arquivo com a lista.\n4 - Formatar arquivo.\n0 - Sair\n\nDigite a opcao:");
        scanf(" %d",&op);
        system("clear");
    }
}
Lista *crialista(){
    Lista *l1 = (Lista*)malloc(sizeof(Lista));
    if(l1!=NULL){
        printf("A lista foi alocada normalmente.\n");
    }
    else{
        printf("Nao foi possivel alocar a lista.\n");
    }
    return l1;
}

void valoreslista(Lista *l1){
    No *no = (No*)malloc(sizeof(No));
    if(no!=NULL && l1->inicio == NULL){
        printf("Digite o nome:\n");
        scanf(" %[^\n]",no->nome);
        l1->inicio = no;
        l1->tamanho = 1;
        no->prox = no;
        printf("Participante cadastrado.\n");
    }
    else if(no!=NULL && l1->inicio !=NULL){
        No *aux;
        aux = l1->inicio;
        while(aux->prox!=l1->inicio){
            aux = aux->prox;
        }
        printf("Digite o nome:\n");
        scanf(" %[^\n]",no->nome);
        aux->prox = no;
        no->prox = l1->inicio;
        l1->tamanho = l1->tamanho + 1;
        printf("Participante cadastrado.\n");
    }
    else if(no==NULL){
        printf("Nao foi possivel alocar o elemento da lista.\n");
    }
}

void imprimearquivo(Lista *l1){
    FILE *arq;
    arq = fopen("Listamercado.txt","a");
    if(arq!=NULL){
        No *aux=l1->inicio;
        int nsemana,n,i;
        printf("Digite o numero de participantes da semana:\n");
        scanf(" %d",&n);
        for(nsemana=1;nsemana<=41;nsemana++){
            fprintf(arq,"Semana: %d\nParticipantes:\n",nsemana);
            for(i=1;i<=n;i++){
                if(i!=n){
                    fprintf(arq,"%s,",aux->nome);
                }
                else {
                    fprintf(arq,"%s.\n\n",aux->nome);    
                }
                aux = aux->prox;   
            }
        }
        printf("Dados alocados na lista.\n");
        fclose(arq);
    }
    else{
        printf("Nao foi possivel localizar/criar o arquivo.\n");
    }
}

void liberalista(Lista *l1){
    No *aux = l1->inicio,*aux1;
    while(aux->prox!=l1->inicio){
        aux1 = aux->prox;
        free(aux);
        aux = aux1;
    }
    free(l1->inicio);
    free(l1);
    if(l1==NULL){
        printf("Lista liberada com sucesso");
    }
}

void limpararquivo(){
    FILE *arq;
    arq = fopen("Listamercado.txt","w");
    printf("Arquivo formatado.\n");
    fclose(arq);
}

void imprimelista(Lista *l1){
    if(l1==NULL){
        printf("Lista vazia.\n");
    }
    else{
        No *aux = l1->inicio;
        printf("Tamanho da lista: %d.\nNomes da lista:\n",l1->tamanho);
        while(aux->prox!=l1->inicio){
            printf("%s\n",aux->nome);
            aux = aux->prox;
        }
        printf("%s\n",aux->nome);  
    }
}