#ifndef __ARQUIVO_H__
#define __ARQUIVO_H__

#include <errno.h>

#include "tipos.h"

extern int errno;

void retornarValoresCSV(char *linha, dicaPalavra *retorno)
{
    char *token;

    token = strtok(linha, ",");
    strcpy(retorno->palavra, token);

    token = strtok(NULL, "\n");
    strcpy(retorno->dica, token);
}

short int possuiVirgula(const char *linha)
{
	short int i = 0;
	for (i = 0; i < strlen(linha); i++) {
	    if (',' == linha[i]) {
	        return 1;
	    }
	}

	return 0;
}

int carregarListaPalavras(node **listaPalavras, const char* nomeArquivo)
{
    int totalElementos = 0;
    char linha[MAX_CHAR];


    FILE *fp = NULL;
    fp = fopen(nomeArquivo, "r");
    if(! fp) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return errno;
    }

    dicaPalavra palavras;
    while (fgets(linha, MAX_CHAR, fp)) {
        totalElementos++;

		if (! possuiVirgula(linha)) {
		    fprintf(stderr, "Value of errno: %d\n", errno);
		    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
		    return errno;
		}


		retornarValoresCSV(linha, &palavras);
		node *palavra = retornarNovoNo(&palavras);
        palavra->px = (*listaPalavras);
        (*listaPalavras) = palavra;
    }

    fclose(fp);


    return totalElementos ? ++totalElementos : 0;
}


#endif