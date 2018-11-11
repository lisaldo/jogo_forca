#include "forca.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main()
{
    int totalElementos = 0;
    node *  palavra = NULL;
    node *listaPalavras = NULL;
    char linha[MAX_CHAR];

    FILE *fp = NULL;
    fp = fopen("palavras.csv", "r");
    if (! fp) {
        return -1;
    }

    while (fgets(linha, MAX_CHAR, fp)) {
        totalElementos++;
        if (! listaPalavras) {
            listaPalavras = retornarNovoNo(linha);
            palavra = listaPalavras;
            continue;
        }

        palavra->px = retornarNovoNo(linha);
        palavra = palavra->px;
    }


    imprimirLista(listaPalavras, 0);
    printf("\n");
    apagarLista(listaPalavras);

    return 0;
}
