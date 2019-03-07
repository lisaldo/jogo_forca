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

typedef struct {
    char dica[MAX_CHAR];
    char palavra[MAX_CHAR];
} dicaPalavra;

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

node* retornarNovoNo(const dicaPalavra *palavras)
{
	node *p = (node*) calloc(1, sizeof(node));

	p->tamanhoPalavra = strlen(palavras->palavra);
	p->quantidadeLetras = retornarQuantidadeLetras(palavras->palavra);

	strcpy(p->nome, palavras->palavra);
	strcpy(p->dica, palavras->dica);
	p->jaUsada = 0;
	p->px = NULL;

	return p;
}

#endif