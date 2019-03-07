#ifndef __TIPOS_H__
#define __TIPOS_H__

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

node retornaNoVazio()
{
    node retorno;
    strcpy(retorno.nome, "vazio");
    strcpy(retorno.dica, "palavra não encontrada");
    retorno.px = NULL;
    retorno.jaUsada = 1;

    return retorno;
}

int retornarQuantidadeLetras(const char *palavra)
{
    int i;
    int total = 0;
    for (i = 0; palavra[i] != '\0'; i++) {
        if (palavra[i] != ' ' && palavra[i] != '-') {
            total++;
        }
    }

    return total;
}

node* retornarNovoNo(char **palavraDica)
{
	node *p = (node*) calloc(1, sizeof(node));

	p->tamanhoPalavra = strlen(palavraDica[0]);
	p->quantidadeLetras = retornarQuantidadeLetras(palavraDica[0]);

	strcpy(p->nome, palavraDica[0]);
	strcpy(p->dica, palavraDica[1]);
	p->jaUsada = 0;
	p->px = NULL;

	return p;
}

#endif