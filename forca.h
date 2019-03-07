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

#include "tipos.h"
#include "arquivo.h"
#include "cross_sistema.h"
#include "numeros.h"

extern int errno;

node retornarElemento(node *no, int numero)
{
    int i = 0;
    node *novoNo = no;

    numero--;
    while (novoNo) {
        printf("Palavra: %s\njaUsada: %d\n", novoNo->nome, novoNo->jaUsada);
        if (novoNo->jaUsada) {
            novoNo = novoNo->px;
            continue;
        }

        if (i == numero || numero == -1) {
            break;
        }

        novoNo = novoNo->px;
        i++;
    }

    if (! novoNo) {
        return retornaNoVazio();
    }

    novoNo->jaUsada = 1;

    return *novoNo;
}

void imprimirLista(node *no, int valor)
{
    if (! no) {
        return;
    }

    valor++;
    printf("%d - Palavra: %s\n", valor, no->nome);
    printf("%d - Dica: %s\n", valor, no->dica);
    imprimirLista(no->px, valor);
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

int escolherLetra(const node *noSorteado, char *palavraSorteada)
{
    char letra;
    int i;
    int acertou = 0;
    printf("Digite uma letra: ");
    scanf(" %c%*c", &letra);
    letra = tolower(letra);
    for (i = 0; i < noSorteado->tamanhoPalavra; ++i) {
        if (tolower(noSorteado->nome[i]) == letra && palavraSorteada[i] != letra) {
            acertou++;
            palavraSorteada[i] = noSorteado->nome[i];
        }
    }

    return acertou;
}

void iniciarForca(const node *noSorteado, char *palavraSorteada)
{
    int acertos = 0;
    int totalAcerto = 0;
    int totalErros = 0;
    while (totalErros < TOTAL_TENTATIVAS) {
        limparTela();
        imprimirBoneco(totalErros);
        imprimirPalavra(noSorteado, palavraSorteada);

        acertos = escolherLetra(noSorteado, palavraSorteada);
        if (! acertos) {
            totalErros++;
        }

        totalAcerto += acertos;
        if (totalAcerto == noSorteado->quantidadeLetras) {
            limparTela();
            imprimirBoneco(totalErros);
            imprimirPalavra(noSorteado, palavraSorteada);
            printf("Parabéns, você acertou!!!\n");
            break;
        } else if (totalErros >= TOTAL_TENTATIVAS) {
            limparTela();
            imprimirBoneco(totalErros);
            printf("Você foi enforcado, tente na próxima\n");
            printf("A palavra era: %s\n", noSorteado->nome);
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
    totalElementos = carregarListaPalavras(&listaPalavras, NOME_ARQUIVO);

    while (1) {
        if (totalElementos < 1) {
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
