//
// Created by lisaldo on 11/9/18.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef FORCA_PALAVRA_H
#define FORCA_PALAVRA_H

#define MAX_CHAR 512

typedef struct node{
    char nome[MAX_CHAR];
    char dica[MAX_CHAR];
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

node* retornarNovoNo(char *linha)
{
    char *palavraDica[2];

    retornarValoresCSV(linha, palavraDica);
    node *p = (node*) calloc(1, sizeof(node));
    strcpy(p->nome, palavraDica[0]);
    strcpy(p->dica, palavraDica[1]);
    p->px = NULL;

    free(palavraDica[0]);
    free(palavraDica[1]);

    return p;
}


#endif //FORCA_PALAVRA_H
