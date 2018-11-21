//
// Created by lisaldo on 11/9/18.
//

#ifndef FORCA_PALAVRA_H
#define FORCA_PALAVRA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>

extern int errno;

#ifdef WIN32

#include <windows.h>
double getTime()
{
    LARGE_INTEGER t, f;
    QueryPerformanceCounter(&t);
    QueryPerformanceFrequency(&f);
    return (double)t.QuadPart/(double)f.QuadPart;
}

void limparTela()
{
    system("cls");
}

#else

#include <sys/time.h>
#include <sys/resource.h>
double getTime()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

void limparTela()
{
    system("clear");
}

#endif

#define MAX_CHAR 200
#define TOTAL_TENTATIVAS 6
#define NOME_ARQUIVO "palavras.csv"

typedef struct node{
    int tamanhoPalavra;
    int quantidadeLetras;
    char nome[MAX_CHAR];
    char dica[MAX_CHAR];
    short int jaUsada;
    struct node *px;
} node;

void retornarValoresCSV(char *linha, char **retorno)
{
    char *token;
    token = strtok(linha, ";");

    retorno[0] = calloc(strlen(token), sizeof(char));
    strcpy(retorno[0], token);

    token = strtok(NULL, "\n");
    retorno[1] = calloc(strlen(token), sizeof(char));
    strcpy(retorno[1], token);
}

int retornarQuantidadeLetras(const char *palavra)
{
    int i;
    int total = 0;
    for (i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] != ' ' && palavra[i] != '-') {
            printf("Letra: '%c'\n", palavra[i]);
            total++;
        }
    }

    return total;
}

node* retornarNovoNo(char *linha)
{
    short int possuiPontoVirgula = 0;
    short int i = 0;
    for (i = 0; i < strlen(linha); i++) {
        if (';' == linha[i]) {
            possuiPontoVirgula = 1;
        }
    }

    if (! possuiPontoVirgula) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return NULL;
    }

    char *palavraDica[2];

    retornarValoresCSV(linha, palavraDica);
    node *p = (node*) calloc(1, sizeof(node));

    p->tamanhoPalavra = strlen(palavraDica[0]);
    p->quantidadeLetras = retornarQuantidadeLetras(palavraDica[0]);

    strcpy(p->nome, palavraDica[0]);
    strcpy(p->dica, palavraDica[1]);
    p->jaUsada = 0;
    p->px = NULL;

    free(palavraDica[0]);
    free(palavraDica[1]);

    return p;
}

node retornarElemento(node *no, int numero)
{
    int i = 0;
    node *novoNo = no;
    while (novoNo && numero > i) {
        if (! novoNo->jaUsada) {
            i++;
        }

        novoNo = novoNo->px;
    }

    if (! novoNo) {
        node retorno;
        strcpy(retorno.nome, "vazio");
        strcpy(retorno.dica, "palavra não encontrada");
        retorno.px = NULL;
        retorno.jaUsada = 1;
        return retorno;
    }

    novoNo->jaUsada = 1;

    return *novoNo;
}

/*
 * Código de geração de números aleatórios modificado baseado no link abaixo
 * fonte: https://rosettacode.org/wiki/Statistics/Normal_distribution#C
 */
int numeroAleatorio(void)
{
    double retorno;
    double valorMuitoGrande = 959598903;
    double seed = 1000000 * (valorMuitoGrande - getTime());
    srand((unsigned int) seed);
    double x,y,rsq,f;
    do {
        x = 2.0 * rand() / (double)RAND_MAX - 1.0;
        y = 2.0 * rand() / (double)RAND_MAX - 1.0;
        rsq = x * x + y * y;
    } while (rsq >= 1. || rsq == 0.);

    f = sqrt( -2.0 * log(rsq) / rsq );
    retorno =  1000 * x * f * y;
    retorno = (retorno >= 0) ? retorno : (retorno*(-1));

    return (int) retorno;
}

int numeroAleatorioRange(int menor, int maior)
{
    maior--;
    int retorno = ((numeroAleatorio() % (maior - menor + 1)) + menor);

    return retorno;
}

int carregarListaPalavras(node **listaPalavras)
{
    int totalElementos = 0;
    char linha[MAX_CHAR];


    FILE *fp = NULL;
    fp = fopen(NOME_ARQUIVO, "r");
    if(! fp) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return -1;
    }

    while (fgets(linha, MAX_CHAR, fp)) {
        totalElementos++;

        node *palavra = retornarNovoNo(linha);
        palavra->px = (*listaPalavras);
        (*listaPalavras) = palavra;
    }

    fclose(fp);

    return totalElementos;
}

void imprimir_lista(node *no, int valor)
{
    if (! no) {
        return;
    }

    valor++;
    printf("%d - Palavra: %s\n", valor, no->nome);
    printf("%d - Dica: %s\n", valor, no->dica);
    imprimir_lista(no->px, valor);
}

void apagarLista(node *no)
{
    if (! no) {
        return;
    }

    apagarLista(no->px);
    free(no);
}

void imprimirBoneco(int erro)
{
    printf("============= FORCA ==================\n");
    if (! erro) {
        printf("\nPor enquanto tá vivo \n\n");
    }

    if (erro >= 1) {
        printf("     O    \n");
    }

    if (erro == 2) {
        printf("     |    \n");
    }

    if (erro == 3) {
        printf("    /|    \n");
    }

    if (erro >= 4) {
        printf("    /|\\   \n");
    }

    if (erro == 5) {
        printf("    /     \n");
    }

    if (erro >= 6) {
        printf("    /¨\\   \n");
    }

    printf("======================================\n");
}

void imprimirPalavra(const node *retorno, const char *palavraSorteada)
{
    printf("Palavra: %s (%d letras)\n", palavraSorteada, retorno->quantidadeLetras);
    printf("Dica: %s\n", retorno->dica);
}

int escolherLetra(const node *retorno, char *palavraSorteada)
{
    char letra;
    int i;
    int acertou = 0;
    printf("Digite uma letra: ");
    scanf(" %c%*c", &letra);
    letra = tolower(letra);
    for (i = 0; i < retorno->tamanhoPalavra; ++i) {
        if (tolower(retorno->nome[i]) == letra && palavraSorteada[i] != letra) {
            acertou++;
            palavraSorteada[i] = retorno->nome[i];
        }
    }

    return acertou;
}

void iniciarForca(const node *retorno, char *palavraSorteada)
{
    int acertos = 0;
    int totalAcerto = 0;
    int totalErros = 0;
    while (totalErros < TOTAL_TENTATIVAS) {
        limparTela();
        imprimirBoneco(totalErros);
        imprimirPalavra(retorno, palavraSorteada);

        acertos = escolherLetra(retorno, palavraSorteada);
        if (! acertos) {
            totalErros++;
        }

        totalAcerto += acertos;
        if (totalAcerto == retorno->quantidadeLetras) {
            limparTela();
            imprimirBoneco(totalErros);
            imprimirPalavra(retorno, palavraSorteada);
            printf("Parabéns, você acertou!!!\n");
            break;
        } else if (totalErros >= TOTAL_TENTATIVAS) {
            limparTela();
            imprimirBoneco(totalErros);
            printf("Você foi enforcado, tente na próxima\n");
            printf("A palavra era: %s\n", retorno->nome);
            break;
        }
    }
}

void mascararPalavra(const node* retorno, char *palavraSorteada)
{
    int i;
    for (i = 0; i < retorno->tamanhoPalavra; i++) {
        if (retorno->nome[i] == ' ' || retorno->nome[i] == '-') {
            palavraSorteada[i] = retorno->nome[i];
        } else {
            palavraSorteada[i] = '_';
        }

        palavraSorteada[i + 1] = '\0';
    }
}

int rodarJogo()
{
    int totalElementos = 0;
    char resposta;
    char palavraSorteada[MAX_CHAR];
    node *listaPalavras = NULL;
    totalElementos = carregarListaPalavras(&listaPalavras);

    while (1) {
        if (totalElementos <= 0) {
            printf("Não foram encontradas palavras no arquivo %s\n", NOME_ARQUIVO);
            return -1;
        }

        node retorno = retornarElemento(listaPalavras, numeroAleatorioRange(0, totalElementos));
        if (! strcmp(retorno.nome, "vazio")) {
            printf("Não foram encontradas palavras no arquivo palavras.csv\n");
            return -1;
        }

        mascararPalavra(&retorno, palavraSorteada);
        iniciarForca(&retorno, palavraSorteada);

        printf("Digite 's' para continuar jogando: ");
        scanf(" %c%*c", &resposta);
        if (tolower(resposta) == 's') {
            totalElementos--;
            continue;
        }

        printf("Tchaaaau!!!!\n");
        break;
    }

    apagarLista(listaPalavras);

    return 0;
}

#endif //FORCA_PALAVRA_H
