#ifndef __NUMEROS_H__
#define __NUMEROS_H__

#include <math.h>

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
    int retorno = ((numeroAleatorio() % (maior - menor + 1)) + menor);

    return retorno;
}

#endif