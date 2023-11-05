/********************************************

AUTOR: LUCAS DAVID ROSCZINIAK COSTA

*********************************************

DESCRIÇÃO: Sistema ETL programado em C
utilizando leitura de dados de arquivos .txt
e armazenamento em listas encadeadas ou listas
sequenciais.

Métodos para listas sequenciais:

- Armazenamento de dados em lista sequencial
- Adicionar no inicio da lista
- Adicionar no meio da lista
- Adicionar no fim da lista
- Remover do inicio da lista
- Remover no meio da lista
- Remover no fim da lista
- Busca sequencial de dados da lista
- Busca binaria de dados da lista
- Ordenacao da lista usando o metodo Selection
- Ordenacao da lista usando o metodo Insertion
- Ordenacao da lista usando o metodo Bubble
- Ordenacao da lista usando o metodo Shell
- Ordenacao da lista usando o metodo Quick
- Impressao da lista
- Salvar lista em novo arquivo .txt

Métodos para listas encadeadas:

- Armazenamento de dados em lista encadeada
- Adicionar no inicio da lista
- Adicionar no meio da lista
- Adicionar no fim da lista
- Remover do inicio da lista
- Remover no meio da lista
- Remover no fim da lista
- Busca sequencial de dados da lista
- Impressao da lista
- Salvar lista em novo arquivo .txt

********************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHOALOCACAO 20000000

int tamanho = 0;
int listaordenada=0;

/********************************************
          MÉTODOS LISTA ENCADEADA
********************************************/

typedef struct{
 int rg;
 char nome[50];
 struct no *proximo;
} NoEncadeada;

/********************************************

MÉTODO: leArquivoEncadeada()

DESCRIÇÃO: Lê os arquivos do arquivo .txt
e insere-os dentro de uma lista encadeada.

Por algum motivo foram inseridos 2 dados a
mais na lista(1 no começo e 1 no fim), por
isso chamei as funcoes removerFim() e
removerInicio().

********************************************/

NoEncadeada* leArquivoEncadeada(){

    char nomearquivo[50];
    FILE* file=NULL;
    char nome[50], c;
    int rg;
    NoEncadeada* primeiro = NULL;
    NoEncadeada* ultimo = NULL;

    printf("\nDigite o nome do arquivo que deseja abrir no seguinte formato: ./NOMEDOARQUIVO.txt:\n");
    scanf("%s", nomearquivo);

    file = fopen(nomearquivo, "r");

    while(file==NULL){
        printf("Erro na leitura do arquivo, cheque se o nome passado esta correto e se o arquivo consta na mesma pasta do programa!\n\n");
        printf("Digite o nome do arquivo que deseja abrir no seguinte formato: ./NOMEDOARQUIVO.txt:\n");
        scanf("%s", nomearquivo);
        file = fopen(nomearquivo, "r");
    }


    while(!feof(file)) {

        NoEncadeada* novo = (NoEncadeada*)malloc(sizeof(NoEncadeada));
        fscanf(file,"%[^,]s", &nome);
        c=fgetc(file);
        fscanf(file,"%d", &rg);
        c=fgetc(file);

        strcpy(novo->nome, nome);
        novo->rg=rg;
        novo->proximo=NULL;

        if (primeiro == NULL)
        {
            primeiro = novo;
            ultimo = novo;
        }
        else
        {
            ultimo->proximo = novo;
            ultimo = novo;
        }
        tamanho++;
    }
    fclose(file);

    return primeiro;
}

/********************************************

MÉTODO: salvarArquivoEncadeada()

DESCRIÇÃO: Faz a leitura dos dados da lista
e insere-os dentro de um novo arquivo .txt
nomeado de NovaListaEncadeada.txt, o arquivo fica
disponível dentro do diretório em que estão
os outros arquivos .txt e os arquivos .c.

********************************************/

void salvarArquivoEncadeada(NoEncadeada **dados){

    FILE *file = fopen("./NovaListaEncadeada.txt", "w");
    NoEncadeada *aux;
    aux = malloc(sizeof(NoEncadeada));
    aux=*dados;
    while(aux!=NULL){
        fprintf(file, "%s", aux->nome);
        fprintf(file, ",");
        fprintf(file, "%d", aux->rg);
        fprintf(file, "\n");
        aux=aux->proximo;
    }
    fclose(file);
}

/********************************************

MÉTODO: menuEncadeada()

DESCRIÇÃO: Printa um menu e retorna a escolha
do usuário.

********************************************/

int menuEncadeada(){
    int resposta;
    printf("1 - Mostrar lista\n2 - Adicionar informacao no inicio da lista\n3 - Adicionar informacao no meio da lista");
    printf("\n4 - Adicionar informacao no fim da lista\n5 - Remover informacao do inicio da lista");
    printf("\n6 - Remover informacao do meio da lista\n7 - Remover informacao do fim da lista");
    printf("\n8 - Buscar dados\n0 - Salvar e sair do sistema\nOpcao: ");
    scanf("%d", &resposta);
    return resposta;
}

/********************************************

MÉTODO: imprimirEncadeada()

DESCRIÇÃO: Percorre dados armazenados na
lista e printa-os.

********************************************/

void imprimirEncadeada(NoEncadeada *no){

    printf("\n");
    while(no){
        printf("%s %d\n", no->nome, no->rg);
        no=no->proximo;
    }
    printf("\n");
}

/********************************************

MÉTODO: buscaSequencialEncadeada()

DESCRIÇÃO: Realiza a busca pelo rg passado
por parâmetro utilizando o metodo busca sequencial
 e printa informações do dado buscado,
tempo de execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void buscaSequencialEncadeada(NoEncadeada **dados, int rg, int tamanho){

    int i=1, rgexiste=0, c, m;
    NoEncadeada *aux;
    double tempo_execucao = 0.0;

    clock_t inicio = clock();

    aux = malloc(sizeof(NoEncadeada));

    aux=*dados;
    while(i<=tamanho){
        if(rg==aux->rg){
            rgexiste=1;
            break;
        }
        aux=aux->proximo;
        i++;
    }

    clock_t fim = clock();
    tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;

    c=i*2;
    m=i+1;

    if(rgexiste){
        printf("\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", aux->nome, aux->rg, i, tempo_execucao);
        printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
    }
    else{
    printf("\nNenhuma pessoa encontrada com esse RG\n\n");
    }
}

/********************************************

MÉTODO: inserirInicioEncadeada()

DESCRIÇÃO: Insere os dados lidos na
primeira posição da lista eprinta informações
do dado removido, tempo de execução da função,
C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void inserirInicioEncadeada(NoEncadeada **dados){

    NoEncadeada *novo;
    double tempo_execucao = 0.0;

    novo = malloc(sizeof(NoEncadeada));

    printf("Nome: ");
    scanf("%s", &novo->nome);
    printf("RG: ");
    scanf("%d", &novo->rg);

    clock_t inicio = clock();

    novo->proximo= *dados;
    *dados=novo;

    clock_t fim = clock();
    tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n\nDados inseridos:\nNome: %s\nRG: %d\nPosicao na lista: 1\nTempo de execucao: %f", novo->nome, novo->rg, tempo_execucao);
    printf("\nC(n) - 0\nM(n) - 5\n\n");
}

/********************************************

MÉTODO: inserirMeioEncadeada()

DESCRIÇÃO: Insere os dados lidos na posição n
da lista e printa informações do dado removido,
tempo de execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void inserirMeioEncadeada(NoEncadeada **dados){

    NoEncadeada *aux, *novo;
    int n, i=0, m, c;
    double tempo_execucao = 0.0;

    novo = malloc(sizeof(NoEncadeada));

    printf("Nome: ");
    strcpy(novo->nome, "lucas");
    scanf("%s", &novo->nome);
    printf("RG: ");
    scanf("%d", &novo->rg);
    printf("Digite a posição que voce deseja armazenar as informacoes: ");
    scanf("%d", &n);

    clock_t inicio = clock();

    aux = malloc(sizeof(NoEncadeada));

    aux=*dados;
    while(i<n-2){
        aux=aux->proximo;
        i++;
    }
    novo->proximo = aux->proximo;
    aux->proximo=novo;

    clock_t fim = clock();
    tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;

    c=i;
    m=i+7;

    printf("\n\nDados inseridos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", novo->nome, novo->rg, n, tempo_execucao);
    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
}

/********************************************

MÉTODO: inserirFimEncadeada()

DESCRIÇÃO: Insere os dados lidos na última
posição da lista e printa informações do
dado removido, tempo de execução da função,
C(n) e M(n).

*Esse método é utilizado para realizar a
leitura de dados informados pelo usuário
e armazena-los na lista.

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void inserirFimEncadeada(NoEncadeada **dados){

    NoEncadeada *aux, *novo;
    double tempo_execucao = 0.0;
    int i=0, c, m;

    novo = malloc(sizeof(NoEncadeada));

    printf("Nome: ");
    scanf("%s", &novo->nome);
    printf("RG: ");
    scanf("%d", &novo->rg);

    clock_t inicio = clock();

    aux = malloc(sizeof(NoEncadeada));

    novo->proximo=NULL;

    aux=*dados;
    while(aux->proximo){
        aux=aux->proximo;
        i++;
    }
    aux->proximo=novo;

    clock_t fim = clock();
    tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;

    c=i;
    m=i+7;

    printf("\n\nDados inseridos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", novo->nome, novo->rg, i+2, tempo_execucao);
    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
}

/********************************************

MÉTODO: removerInicioEncadeada()

DESCRIÇÃO: Remove os dados da primeira
posição da lista e printa informações do
dado removido, tempo de execução da função,
C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void removerInicioEncadeada(NoEncadeada **dados, int print){
    NoEncadeada *aux;
    char nome[50];
    int rg;
    double tempo_execucao = 0.0;

    clock_t inicio = clock();

    aux=*dados;
    rg=aux->rg;
    strcpy(nome, aux->nome);
    *dados=aux->proximo;
    aux=*dados;

    clock_t fim = clock();
    tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;


    if(print){
        printf("\n\nDados removidos:\nNome: %s\nRG: %d\nPosicao na lista: 1\nTempo de execucao: %f", nome, rg, tempo_execucao);
        printf("\nC(n) - 0\nM(n) - 3\n\n");
    }
}

/********************************************

MÉTODO: removerMeioEncadeada()

DESCRIÇÃO: Remove os dados da posição n
passada por parâmetro da lista e printa
informações do dado removido, tempo de
execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void removerMeioEncadeada(NoEncadeada **dados, int n){

    NoEncadeada *aux, *remover;
    int i=1, c, m;
    double tempo_execucao = 0.0;

    clock_t inicio = clock();

    aux=*dados;
    while(i<n-1){
        aux=aux->proximo;
        i++;
    }
    remover=aux->proximo;
    aux->proximo = remover->proximo;

    clock_t fim = clock();
    tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;

    c=  i;
    m = c+2;

    printf("\n\nDados removidos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", remover->nome, remover->rg, n, tempo_execucao);
    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
}

/********************************************

MÉTODO: removerFim()

DESCRIÇÃO: Remove os dados da posição final
da lista e printa informações do dado removido,
tempo de execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void removerFimEncadeada(NoEncadeada **dados, int n, int print){
    NoEncadeada *aux, *remover;
    int i=1, c, m;
    double tempo_execucao = 0.0;

    clock_t inicio = clock();

    aux=*dados;
    while(i<n-1){
        aux=aux->proximo;
        i++;
    }

    remover=aux->proximo;
    aux->proximo=NULL;

    clock_t fim = clock();
    tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;

    c=i;
    m=c+2;

    if(print){
        printf("\n\nDados removidos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", remover->nome, remover->rg, n, tempo_execucao);
        printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
    }
}

/********************************************
          MÉTODOS LISTA SEQUENCIAL
********************************************/

typedef struct{
 int rg;
 char nome[50];
} NoSequencial;

/********************************************

MÉTODO: leArquivoSequencial()

DESCRIÇÃO: Lê os arquivos do arquivo .txt
e insere-os dentro de uma lista sequencial.

********************************************/

int lerArquivoSequencial(NoSequencial *dados){
    char nome[50], c;
    int rg, tamanho=1;
    FILE *file;
    char nomearquivo[50];

    printf("Digite o nome do arquivo que deseja abrir no seguinte formato: ./NOMEDOARQUIVO.txt:\n");
    scanf("%s", nomearquivo);

    file = fopen(nomearquivo, "r");

    while(file==NULL){
        printf("Erro na leitura do arquivo, cheque se o nome passado esta correto e se o arquivo consta na mesma pasta do programa!\n\n");
        printf("Digite o nome do arquivo que deseja abrir no seguinte formato: ./NOMEDOARQUIVO.txt:\n");
        scanf("%s", nomearquivo);
        file = fopen(nomearquivo, "r");
    }

    while(!feof(file)) {

        fscanf(file,"%[^,]s", &nome);
        c=fgetc(file);
        fscanf(file,"%d", &rg);
        c=fgetc(file);
        strcpy(dados[tamanho-1].nome, nome);
        dados[tamanho-1].rg=rg;
        tamanho++;
    }
    fclose(file);
    dados[tamanho-2].rg=NULL;
    dados[tamanho-1].rg=NULL;
    tamanho-=2;

    return tamanho;
}

/********************************************

MÉTODO: salvarArquivoSequencial()

DESCRIÇÃO: Faz a leitura dos dados da lista
e insere-os dentro de um novo arquivo .txt
nomeado de NovaListaSequencial.txt, o arquivo
fica disponível dentro do diretório em que
estão os outros arquivos .txt e os arquivos
.c.

********************************************/

void salvarArquivoSequencial(NoSequencial *dados, int tamanho){

    int i;

    FILE *newfile = fopen("./NovaListaSequencial.txt", "w");

        for(i=0;i<tamanho;i++){
            fprintf(newfile, "%s", dados[i].nome);
            fprintf(newfile, ",");
            fprintf(newfile, "%d", dados[i].rg);
            fprintf(newfile, "\n");
        }
        fclose(newfile);
}

/********************************************

MÉTODO: menuSequencial()

DESCRIÇÃO: Printa um menu e retorna a escolha
do usuário.

********************************************/

int menuSequencial(){
    int resposta;
    printf("1 - Mostrar lista\n2 - Adicionar informacao no inicio da lista\n3 - Adicionar informacao no meio da lista");
    printf("\n4 - Adicionar informacao no fim da lista\n5 - Remover informacao do inicio da lista");
    printf("\n6 - Remover informacao do meio da lista\n7 - Remover informacao do fim da lista");
    printf("\n8 - Buscar dados\n9 - Busca binaria ");
    printf("\n10 - Selection sort\n11 - Insertion sort ");
    printf("\n12 - Bubble sort\n13 - Shell sort ");
    printf("\n14 - Quick sort");
    printf("\n0 - Salvar e sair do sistema\nOpcao: ");
    scanf("%d", &resposta);
    return resposta;
}

/********************************************

MÉTODO: imprimirSequencial()

DESCRIÇÃO: Percorre dados armazenados na
lista e printa-os.

********************************************/

void imprimirSequencial(NoSequencial *dados, int tamanho){

    int i;
    printf("\n");
    for(i=0;i<tamanho;i++){
        printf("%s %d", dados[i].nome, dados[i].rg);
        printf("\n");
    }
    printf("\n");
    printf("\n");
}

/********************************************

MÉTODO: buscarSequencialSequencial()

DESCRIÇÃO: Realiza a busca pelo rg lido
utilizando o metodo busca sequencial e
printa informações do dado buscado,
tempo de execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void buscaSequencialSequencial(NoSequencial *dados, int tamanho){

    int i, rg, buscaexiste, c, m;

    printf("Digite o RG que deseja buscar: ");
    scanf("%d", &rg);

    double tempo_execucao = 0.0;

    clock_t inicio = clock();

    for(i=0;i<tamanho;i++){
        if(dados[i].rg==rg){
            buscaexiste=1;
            clock_t fim = clock();
            tempo_execucao += (double)(fim - inicio) / CLOCKS_PER_SEC;
            c=i*2;
            m=0;
            printf("\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", dados[i].nome, dados[i].rg, i+1, tempo_execucao);
            printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
            break;
        }
    }
    if(!buscaexiste){
        printf("Nenhum dado foi encontrado!\n");
    }
}

/********************************************

MÉTODO: buscaBinaraSequencial()

DESCRIÇÃO: Realiza a busca pelo rg lido
utilizando o metodo busca binaria e
printa informações do dado buscado,
tempo de execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void buscaBinariaSequencial(NoSequencial *dados, int tamanho){

    int i, rg, e=-1, d=tamanho, dadoexiste=0, c=0, m=0;

    printf("Digite o RG que deseja buscar: ");
    scanf("%d", &rg);

    double tempo_execucao = 0.0;
    clock_t inicio = clock();

    while(e<d-1){
        c+=4;
        m+=2;

        i=(d+e)/2;

        if(dados[i].rg==rg){
            dadoexiste=1;
            break;
        }
        else if(dados[i].rg>rg){
            d=i;
        }
        else if(dados[i].rg<rg){
            e=i;
        }
    }


    clock_t fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    if(dadoexiste){
        printf("\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", dados[i].nome, dados[i].rg, i+1, tempo_execucao);
        printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
    }
    else{
        printf("\nDado nao encontrado\n\n");
    }
}

/********************************************

MÉTODO: removerFimSequencial()

DESCRIÇÃO: Remove os dados da posição final
da lista e printa informações do dado removido,
tempo de execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void removerFimSequencial(NoSequencial *dados, int tamanho){

    int rg;
    char nome[50];

    strcpy(nome, dados[tamanho-1].nome);
    rg = dados[tamanho-1].rg;

    double tempo_execucao = 0.0;
    clock_t inicio = clock();

    dados[tamanho-1].rg=NULL;
    strcpy(dados[tamanho-1].nome, "");

    clock_t fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n\nDados removidos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", nome, rg, tamanho-1, tempo_execucao);
    printf("\nC(n) - 0\nM(n) - 2\n\n");
}

/********************************************

MÉTODO: ordenacaoSelecaoSequencial()

DESCRIÇÃO: Ordena dados da lista utilizando o
metodo Selection Sort e printa tempo de
execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void ordenacaoSelecaoSequencial(NoSequencial *dados, int tamanho){

    int menor, menorindex, i, j, c=0, m=0;

    NoSequencial *aux;

    aux =  (NoSequencial*)malloc (sizeof(NoSequencial));

    double tempo_execucao = 0.0;
    clock_t inicio = clock();

    for(j=0;j<tamanho;j++){
        menor=dados[j].rg;
        menorindex=j;
        c++;
        m+=2;
        for(i=j;i<tamanho;i++){
            c+=2;
            if(dados[i].rg<menor){
                menor=dados[i].rg;
                menorindex=i;
                m+=2;
            }

        }
        aux->rg=dados[j].rg;
        strcpy(aux->nome, dados[j].nome);

        dados[j]=dados[menorindex];

        dados[menorindex].rg = aux->rg;
        strcpy(dados[menorindex].nome, aux->nome);

        m+=6;

    }

    clock_t fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n\nOrdenacao feita com sucesso!\nTempo de execucao: %f", tempo_execucao);
    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);

}

/********************************************

MÉTODO: ordenacaoInsercaoSequencial()

DESCRIÇÃO: Ordena dados da lista utilizando o
metodo Insertion Sort e printa tempo de
execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void ordenacaoInsercaoSequencial(NoSequencial *dados, int tamanho){

    int i, j, m=0;
    long double c=0;

    NoSequencial *aux;

    aux =  (NoSequencial*)malloc (sizeof(NoSequencial));

    double tempo_execucao = 0.0;
    clock_t inicio = clock();

    for(i=1;i<tamanho;i++){
        c++;
        for(j=i;j>0;j--){
            c+=2;
            if(dados[j].rg<dados[j-1].rg){

                c++;
                aux->rg=dados[j].rg;
                strcpy(aux->nome, dados[j].nome);

                dados[j].rg=dados[j-1].rg;
                strcpy(dados[j].nome, dados[j-1].nome);

                dados[j-1].rg=aux->rg;
                strcpy(dados[j-1].nome, aux->nome);
                m+=6;
            }
        }
    }

    clock_t fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n\nOrdenacao feita com sucesso!\nTempo de execucao: %f", tempo_execucao);
    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
}

/********************************************

MÉTODO: ordenacaoBubbleSequencial()

DESCRIÇÃO: Ordena dados da lista utilizando o
metodo Bubble Sort e printa tempo de
execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void ordenacaoBubbleSequencial(NoSequencial *dados, int tamanho){

    int i, j, c=0, m=0;

    NoSequencial *aux;

    aux =  (NoSequencial*)malloc (sizeof(NoSequencial));

    double tempo_execucao = 0.0;
    clock_t inicio = clock();

    for(i=0;i<tamanho;i++){
        c++;
        for(j=0;j<tamanho-1;j++){
            c+=2;
            if(dados[j].rg>dados[j+1].rg){

                aux->rg=dados[j].rg;
                strcpy(aux->nome, dados[j].nome);

                dados[j].rg=dados[j+1].rg;
                strcpy(dados[j].nome, dados[j+1].nome);

                dados[j+1].rg=aux->rg;
                strcpy(dados[j+1].nome, aux->nome);

                m+=6;
            }
        }
    }

    clock_t fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n\nOrdenacao feita com sucesso!\nTempo de execucao: %f", tempo_execucao);
    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
}

/********************************************

MÉTODO: ordenacaoShellSequencial()

DESCRIÇÃO: Ordena dados da lista utilizando o
metodo Shell Sort e printa tempo de
execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void ordenacaoShellSequencial(NoSequencial *dados, int tamanho){

    int i, j, h, c=0, m=0;

    NoSequencial *aux;

    aux =  (NoSequencial*)malloc (sizeof(NoSequencial));

    double tempo_execucao = 0.0;
    clock_t inicio = clock();

    h=tamanho-1;

    while(h>1){

        h/=2;
        c++;

        for(i=h;i<tamanho;i++){
            c++;
            m+=2;

            aux->rg=dados[i].rg;
            strcpy(aux->nome, dados[i].nome);

            j = i - h;

            while (j >= 0 && aux->rg < dados[j].rg){

                c++;
                m+=2;

                dados[j+h].rg=dados[j].rg;
                strcpy(dados[j+h].nome, dados[j].nome);

                j-=h;
            }

            dados[j+h].rg=aux->rg;
            strcpy(dados[j+h].nome, aux->nome);
            m+=2;
        }
    }

    clock_t fim = clock();
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n\nOrdenacao feita com sucesso!\nTempo de execucao: %f", tempo_execucao);
    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
}

/********************************************

MÉTODO: ordenacaoQuickSequencial()

DESCRIÇÃO: Ordena dados da lista utilizando o
metodo Quick Sort e printa tempo de
execução da função, C(n) e M(n).

C(n) = Número de comparações entre chaves
M(n) = Número de movimentações de itens(x=y)

********************************************/

void ordenacaoQuickSequencial(NoSequencial *dados, int esq, int dir, int print) {

    int pos, c=0, m=0;
    double tempo_execucao;
    clock_t inicio;
    clock_t fim;

    if(print==1){
        tempo_execucao = 0.0;
        inicio = clock();
    }


    if(esq<dir){
        pos=dividirQuickSequencial(dados,esq,dir, &c, &m);
        ordenacaoQuickSequencial(dados,esq,pos-1, 0);
        ordenacaoQuickSequencial(dados,pos+1,dir, 0);
    }

    if(print==1){

        fim = clock();
        tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("\n\nOrdenacao feita com sucesso!\nTempo de execucao: %f", tempo_execucao);
        printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
    }
}

int dividirQuickSequencial(NoSequencial *dados, int esq, int dir, int *c, int *m){

    int i, cont=esq;

    NoSequencial *aux;
    aux =  (NoSequencial*)malloc (sizeof(NoSequencial));

    for(i=esq+1;i<=dir;i++){

        if(dados[i].rg<dados[esq].rg){

            cont++;

            aux->rg=dados[i].rg;
            strcpy(aux->nome, dados[i].nome);

            dados[i].rg=dados[cont].rg;
            strcpy(dados[i].nome, dados[cont].nome);

            dados[cont].rg=aux->rg;
            strcpy(dados[cont].nome, aux->nome);

            *m+=6;
        }
        *c+=2;
    }
    aux->rg=dados[esq].rg;
    strcpy(aux->nome, dados[esq].nome);

    dados[esq].rg=dados[cont].rg;
    strcpy(dados[esq].nome, dados[cont].nome);

    dados[cont].rg=aux->rg;
    strcpy(dados[cont].nome, aux->nome);

    *m+=6;


    return cont;
}

int main(){

    int encadeadaOuSequencial;

    printf("  ______                     _                _       \n");
    printf(" |  ____|                   | |              | |      \n");
    printf(" | |__   _ __   ___ __ _  __| | ___  __ _  __| | __ _ \n");
    printf(" |  __| | '_ \\ / __/ _` |/ _` |/ _ \\/ _` |/ _` |/ _` |\n");
    printf(" | |____| | | | (_| (_| | (_| |  __/ (_| | (_| | (_| |\n");
    printf(" |______|_| |_|\\___\\__,_|\\__,_|\\___|\\__,_|\\__,_|\\__,_|\n\n");

    printf("                      __   _____ \n");
    printf("                      \\ \\ / / __|\n");
    printf("                       \\ V /\\__ \\\n");
    printf("                        \\_/ |___/\n");

    printf("   _____                                  _       _ \n");
    printf("  / ____|                                (_)     | |\n");
    printf(" | (___   ___  __ _ _   _  ___ _ __   ___ _  __ _| |\n");
    printf("  \\___ \\ / _ \\/ _` | | | |/ _ \\ '_ \\ / __| |/ _` | |\n");
    printf("  ____) |  __/ (_| | |_| |  __/ | | | (__| | (_| | |\n");
    printf(" |_____/ \\___|\\__, |\\__,_|\\___|_| |_|\\___|_|\\__,_|_|\n");
    printf("                 | |                                \n");
    printf("                 |_|                                \n\n");


    printf("1 - Lista Encadeada\n2 - Lista Sequencial\nOpcao: ");
    scanf("%d", &encadeadaOuSequencial);

    if(encadeadaOuSequencial==1){

        NoEncadeada *dadosencadeados=NULL;
        char nome[50];
        int rg, n, resposta;

        dadosencadeados= leArquivoEncadeada();
        removerFimEncadeada(&dadosencadeados, tamanho, 0);
        tamanho--;

        printf("  ______                     _                _       \n");
        printf(" |  ____|                   | |              | |      \n");
        printf(" | |__   _ __   ___ __ _  __| | ___  __ _  __| | __ _ \n");
        printf(" |  __| | '_ \\ / __/ _` |/ _` |/ _ \\/ _` |/ _` |/ _` |\n");
        printf(" | |____| | | | (_| (_| | (_| |  __/ (_| | (_| | (_| |\n");
        printf(" |______|_| |_|\\___\\__,_|\\__,_|\\___|\\__,_|\\__,_|\\__,_|\n\n");

        while(1){
            resposta=menuEncadeada();

            if (resposta==1){
                imprimirEncadeada(dadosencadeados);
            }

            else if(resposta==2){
                inserirInicioEncadeada(&dadosencadeados);
                tamanho++;
            }
            else if(resposta==3){
                inserirMeioEncadeada(&dadosencadeados);
                tamanho++;
            }
            else if(resposta==4){
                inserirFimEncadeada(&dadosencadeados);
                tamanho++;
            }
            else if(resposta==5){
                removerInicioEncadeada(&dadosencadeados, 1);
                tamanho--;
            }
            else if(resposta==6){
                printf("Digite a posicao das informacoes que voce deseja remover: ");
                scanf("%d", &n);
                if(n==1){
                    printf("Para remover as informacoes do primeiro indice da lista seleciona a opcao 5!\n");
                }
                else if(n==tamanho){
                    printf("Para remover as informacoes do ultimo indice da lista seleciona a opcao 7!\n");
                }
                else if(n>tamanho){
                    printf("Esse indice nao existe na lista\n");
                }
                else{
                    removerMeioEncadeada(&dadosencadeados, n);
                    tamanho--;
                }

            }
            else if(resposta==7){
                removerFimEncadeada(&dadosencadeados, tamanho, 1);
                tamanho--;
            }
            else if(resposta==8){
                printf("Digite o RG da pessoa de deseja encontrar: \n");
                scanf("%d", &rg);
                buscaSequencialEncadeada(&dadosencadeados, rg, tamanho);
            }
            else if(resposta==9){
                salvarArquivoEncadeada(&dadosencadeados);
                break;
            }
            else{
                printf("Numero invalido\n");
            }
        }

        free(dadosencadeados);
    }


    else if(encadeadaOuSequencial==2){


        NoSequencial *dados, *novo;
        char nome[50];
        int rg, resposta, i, n, buscaexiste=0, c, m;
        double tempo_execucao;
        clock_t inicio;

        tamanho++;

        dados =  (NoSequencial*)malloc (sizeof(NoSequencial)*TAMANHOALOCACAO);
        tamanho=lerArquivoSequencial(dados);

        printf("   _____                                  _       _ \n");
        printf("  / ____|                                (_)     | |\n");
        printf(" | (___   ___  __ _ _   _  ___ _ __   ___ _  __ _| |\n");
        printf("  \\___ \\ / _ \\/ _` | | | |/ _ \\ '_ \\ / __| |/ _` | |\n");
        printf("  ____) |  __/ (_| | |_| |  __/ | | | (__| | (_| | |\n");
        printf(" |_____/ \\___|\\__, |\\__,_|\\___|_| |_|\\___|_|\\__,_|_|\n");
        printf("                 | |                                \n");
        printf("                 |_|                                \n\n");

        while(1){

            resposta=menuSequencial();

            if (resposta==1){
                imprimirSequencial(dados, tamanho);
            }

            /********************************************

            INSERIR NO INICIO DA LISTA SEQUENCIAL

            Tive dificuldades em criar um método para essa
            funcionalidade, por isso deixei na main mesmo.

            DESCRIÇÃO: Insere os dados lidos na
            primeira posição da lista eprinta informações
            do dado removido, tempo de execução da função,
            C(n) e M(n).

            C(n) = Número de comparações entre chaves
            M(n) = Número de movimentações de itens(x=y)

            ********************************************/

            else if(resposta==2){
                tamanho++;
                novo=NULL;
                novo =  (NoSequencial*)malloc (sizeof(NoSequencial)*TAMANHOALOCACAO);


                printf("Nome: ");
                scanf("%s", &nome);
                printf("RG: ");
                scanf("%d", &rg);

                tempo_execucao = 0.0;
                clock_t inicio = clock();

                for(i=0;i<tamanho;i++){
                   novo[i+1]=dados[i];
                }
                dados=novo;
                strcpy(dados[0].nome, nome);
                dados[0].rg=rg;

                clock_t fim = clock();
                tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                c=i;
                m=i+3;

                printf("\n\nDados inseridos:\nNome: %s\nRG: %d\nPosicao na lista: 1\nTempo de execucao: %f", nome, rg, tempo_execucao);
                printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);

                listaordenada=0;
            }

            /********************************************

            INSERIR NO MEIO DA LISTA SEQUENCIAL

            Tive dificuldades em criar um método para essa
            funcionalidade, por isso deixei na main mesmo.

            DESCRIÇÃO: Insere os dados lidos na posição n
            da lista e printa informações do dado removido,
            tempo de execução da função, C(n) e M(n).

            C(n) = Número de comparações entre chaves
            M(n) = Número de movimentações de itens(x=y)

            ********************************************/

            else if(resposta==3){

                printf("Nome: ");
                scanf("%s", &nome);
                printf("RG: ");
                scanf("%d", &rg);
                printf("Posicao a inserir: ");
                scanf("%d", &n);

                if(n==1){
                    printf("Para adicionar as informacoes no primeiro indice da lista seleciona a opcao 2!\n");
                }
                else if(n==tamanho){
                    printf("Para adicionar as informacoes no ultimo indice da lista seleciona a opcao 4!\n");
                }
                else if(n>tamanho){
                    printf("Esse indice nao existe na lista\n");
                }
                else{
                    tamanho++;
                    novo=NULL;
                    novo =  (NoSequencial*)malloc (sizeof(NoSequencial)*TAMANHOALOCACAO);

                    tempo_execucao = 0.0;
                    clock_t inicio = clock();

                    for(i=0;i<n-1;i++){
                        novo[i]=dados[i];
                    }
                    c=i;
                    for(i=n-1;i<tamanho;i++){
                        novo[i+1]=dados[i];
                    }
                    dados=novo;
                    strcpy(dados[n-1].nome, nome);
                    dados[n-1].rg=rg;

                    clock_t fim = clock();
                    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                    c+=i;
                    m=c+3;

                    printf("\n\nDados inseridos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", nome, rg, n, tempo_execucao);
                    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);

                    listaordenada=0;
                }

            }

            /********************************************

            INSERIR NO FIM DA LISTA SEQUENCIAL

            Tive dificuldades em criar um método para essa
            funcionalidade, por isso deixei na main mesmo.

            DESCRIÇÃO: Insere os dados lidos na última
            posição da lista e printa informações do
            dado removido, tempo de execução da função,
            C(n) e M(n).

            *Esse método é utilizado para realizar a
            leitura de dados informados pelo usuário
            e armazena-los na lista.

            C(n) = Número de comparações entre chaves
            M(n) = Número de movimentações de itens(x=y)

            ********************************************/

            else if(resposta==4){
                tamanho++;

                printf("Nome: ");
                scanf("%s", &nome);
                printf("RG: ");
                scanf("%d", &rg);

                tempo_execucao = 0.0;
                clock_t inicio = clock();

                strcpy(dados[tamanho-1].nome, nome);
                dados[tamanho-1].rg=rg;

                clock_t fim = clock();
                tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                printf("\n\nDados inseridos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", nome, rg, tamanho-1, tempo_execucao);
                printf("\nC(n) - 0\nM(n) - 2\n\n");

                listaordenada=0;
            }

            /********************************************

            REMOVER DO INICIO DA LISTA SEQUENCIAL

            Tive dificuldades em criar um mtodo para essa
            funcionalidade, por isso deixei na main mesmo.

            DESCRIÇÃO: Remove os dados da primeira
            posição da lista e printa informações do
            dado removido, tempo de execução da função,
            C(n) e M(n).

            C(n) = Número de comparações entre chaves
            M(n) = Número de movimentações de itens(x=y)

            ********************************************/
            else if(resposta==5){

                NoSequencial *novo = malloc(sizeof(NoSequencial)*TAMANHOALOCACAO);
                int rg, i;
                char nome[50];

                strcpy(nome, dados[0].nome);
                rg = dados[0].rg;

                double tempo_execucao = 0.0;
                clock_t inicio = clock();

                for(i=0;i<tamanho;i++){
                    novo[i]=dados[i+1];
                }
                dados=novo;
                tamanho--;

                clock_t fim = clock();
                tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                c=i;
                m=i+1;

                printf("\n\nDados removidos:\nNome: %s\nRG: %d\nPosicao na lista: 1\nTempo de execucao: %f", nome, rg, tempo_execucao);
                printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);

            }

            /********************************************

            REMOVER DO MEIO DA LISTA SEQUENCIAL

            Tive dificuldades em criar um mtodo para essa
            funcionalidade, por isso deixei na main mesmo.

            DESCRIÇÃO: Remove os dados da posição n
            da lista e printainformações do dado removido,
            tempo de execução da função, C(n) e M(n).

            C(n) = Número de comparações entre chaves
            M(n) = Número de movimentações de itens(x=y)

            ********************************************/

            else if(resposta==6){

                printf("Posicao a remover: ");
                scanf("%d", &n);

                if(n==1){
                    printf("Para remover as informacoes do primeiro indice da lista seleciona a opcao 5!\n");
                }
                else if(n==tamanho){
                    printf("Para remover as informacoes do ultimo indice da lista seleciona a opcao 7!\n");
                }
                else if(n>tamanho){
                    printf("Esse indice nao existe na lista\n");
                }
                else{

                    int rg;
                    char nome[50];

                    strcpy(nome, dados[n-1].nome);
                    rg = dados[n-1].rg;

                    tempo_execucao = 0.0;
                    clock_t inicio = clock();

                    NoSequencial *novo = malloc(sizeof(NoSequencial)*tamanho);

                    for(i=0;i<n-1;i++){
                        novo[i]=dados[i];
                    }
                    c=i;
                    for(i=n-1;i<tamanho;i++){
                        novo[i]=dados[i+1];
                    }
                    dados=novo;

                    tamanho--;

                    clock_t fim = clock();
                    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

                    c+=i;
                    m=c+1;

                    printf("\n\nDados removidos:\nNome: %s\nRG: %d\nPosicao na lista: %d\nTempo de execucao: %f", nome, rg, n, tempo_execucao);
                    printf("\nC(n) - %d\nM(n) - %d\n\n", c, m);
                }
            }
            else if(resposta==7){

                removerFimSequencial(dados, tamanho);
                tamanho--;
            }
            else if(resposta==8){

                buscaSequencialSequencial(dados, tamanho);
            }
            else if(resposta==9){

                if(listaordenada==1){
                    buscaBinariaSequencial(dados,tamanho);
                }
                else{
                    printf("A lista deve estar ordenada para que seja possivel usar a busca binaria\n\n");
                }


            }
            else if(resposta==10){

                ordenacaoSelecaoSequencial(dados, tamanho);
                listaordenada=1;
            }
            else if(resposta==11){

                ordenacaoInsercaoSequencial(dados, tamanho);
                listaordenada=1;
            }
            else if(resposta==12){

                ordenacaoBubbleSequencial(dados, tamanho);
                listaordenada=1;
            }
            else if(resposta==13){

                ordenacaoShellSequencial(dados, tamanho);
                listaordenada=1;
            }
            else if(resposta==14){

                ordenacaoQuickSequencial(dados, 0, tamanho-1, 1);
                listaordenada=1;
            }
            else if(resposta==0){

                salvarArquivoSequencial(dados, tamanho);
                break;
            }
            else{
                printf("Numero invalido\n");
            }
        }

        free(dados);
        free(novo);
        }
}
