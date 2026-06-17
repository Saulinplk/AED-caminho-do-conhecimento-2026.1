#ifndef JOGADOR_H
#define JOGADOR_H 
                
#include <stdio.h>
#include <string.h>

#include "listad.h"

typedef struct no_estatistica {

    /*
    Isso é a numeração.
    Como o nó em si não teria uma numeração nesse contexto,
    é a numeração DA CASA.
    */
    int numero_casa;              
    int vezes_que_caiu;      

    struct no_estatistica *esq;
    struct no_estatistica *dir;

    /*
    Para sustentar a estrutura pra guardar quantas vezes cada jogador caiu em cada casa 
    (a árvore)
    */

} no_estatistica;

typedef struct {

    no_estatistica *raiz;

    /*
    A árvore, usando um "nó" (ponteiro);
    */

} tp_arvore;

typedef struct jogador {

    char nome[99];

    tp_no *mov;

    /*
    "mov" é pra mover o jogador pelo caminho (lista duplamente encadeada)
    */

    no_estatistica *raiz_estatistica;

    tp_arvore estatisticas;

    int pontos;

    /*
    Basicamente acertos aumentam os pontos, erros diminuem os pontos.
    */

    pergunta acertou[6];
    pergunta errou[6];

    /*
    Para evitar confusão:
    ACERTOU e ERROU são as perguntas em si.
    */

    int quantas_acertou; /* Já aqui é só a quantidade mesmo */
    int quantas_errou;

} jogador;

#endif