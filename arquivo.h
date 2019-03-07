#ifndef __ARQUIVO_H__
#define __ARQUIVO_H__

#include "tipos.h"

void retornarValoresCSV(char *linha, char **retorno)
{
    char *token;
    token = strtok(linha, ",");

    retorno[0] = calloc(strlen(token), sizeof(char));
    strcpy(retorno[0], token);

    token = strtok(NULL, "\n");
    retorno[1] = calloc(strlen(token), sizeof(char));
    strcpy(retorno[1], token);
}

short int possuiVirgula(const char *linha)
{
	short int possuiVirgula = 0;
	short int i = 0;
	for (i = 0; i < strlen(linha); i++) {
	    if (',' == linha[i]) {
	        possuiVirgula = 1;
	    }
	}

	return possuiVirgula;
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
        return -1;
    }

    while (fgets(linha, MAX_CHAR, fp)) {
        totalElementos++;

		if (! possuiVirgula(linha)) {
		    fprintf(stderr, "Value of errno: %d\n", errno);
		    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
		    continue;
		}

		char *palavraDica[2];

		retornarValoresCSV(linha, palavraDica);
		node *palavra = retornarNovoNo(palavraDica);
        palavra->px = (*listaPalavras);
        (*listaPalavras) = palavra;

        free(palavraDica[0]);
		free(palavraDica[1]);
    }

    fclose(fp);


    return totalElementos ? ++totalElementos : 0;
}


#endif