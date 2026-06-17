#ifndef SM_UNIDADE2_H
#define SM_UNIDADE2_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "estrutura_pergunta.h"
#include "listad.h"
#include "jogador.h"
#include "pilha.h"

/*
Análogo ao arquivo da primeira unidade.

A maior diferença é que na função encadear, pula-se as
11 primeiras casas, para não afetar as perguntas
da primeira unidade.
*/

void criarprimeira2 (pergunta perguntas[6]) {

    perguntas[0].nivel = "Facil";

    perguntas[0].enunciado = "Em uma lista duplamente encadeada, cada no possui ponteiros para os nos vizinhos.\n" 
    "Qual eh a principal vantagem estrutural de uma lista duplamente encadeada em relacao a uma lista simplesmente encadeada?\n";

    perguntas[0].alternativas[0] = "a) Ela consome menos memoria do que a simplesmente encadeada por nao precisar de um descritor de fim.;";
    perguntas[0].alternativas[1] = "b) Ela permite a navegacao bidirecional, possibilitando percorrer os elementos tanto para frente quanto para tras.;";
    perguntas[0].alternativas[2] = "c) A insercao de um elemento no inicio da lista tem complexidade de tempo constante, enquanto na lista simples eh linear.;";
    perguntas[0].alternativas[3] = "d) Ela garante que o acesso a qualquer elemento pelo indice seja feito em tempo constante, ou seja, O(1).;";
    perguntas[0].alternativas[4] = "e) Ela dispensa completamente o uso de alocacao dinamica de memoria durante a insercao de novos nos.;";

    perguntas[0].gabarito = 'b';

    perguntas[0].recompensa = 1; 
    perguntas[0].punicao = 1;
}

void criarsegunda2 (pergunta perguntas[6]) {

    perguntas[1].nivel = "Facil";

    perguntas[1].enunciado = "O algoritmo de ordenacao Bubble Sort eh muito conhecido por sua simplicidade.\n"
    "No pior caso (quando o vetor de entrada esta ordenado de forma completamente decrescente), qual eh a complexidade de tempo assintotica desse algoritmo?\n";

    perguntas[1].alternativas[0] = "a) O(n log (n) );";
    perguntas[1].alternativas[1] = "b) O(n);";
    perguntas[1].alternativas[2] = "c) O(n^2);";
    perguntas[1].alternativas[3] = "d) O(1);";
    perguntas[1].alternativas[4] = "e) O(2^n);";

    perguntas[1].gabarito = 'c';

    perguntas[1].recompensa = 1;
    perguntas[1].punicao = 1;
}

void criarterceira2 (pergunta perguntas[6]) {

    perguntas[2].nivel = "Medio";

    perguntas[2].enunciado = "Considere uma lista simplesmente encadeada nao ordenada de tamanho n.\n\n"
    "Se quisermos realizar duas operacoes sequenciais:\n"
    "(1) Buscar um valor especifico na lista\n\n"
    "e\n\n" 
    "(2) Inserir um novo elemento imediatamente apos o no correspondente ao valor encontrado.\n" 
    "Quais sao as respectivas complexidades de tempo para essas duas etapas no pior caso?\n";

    perguntas[2].alternativas[0] = "a) Busca: O(1); Insercao: O(1);";
    perguntas[2].alternativas[1] = "b) Busca: O(n); Insercao: O(n);";
    perguntas[2].alternativas[2] = "c) Busca: O( log (n) ); Insercao: O(1);";
    perguntas[2].alternativas[3] = "d) Busca: O(n); Insercao: O(1);";
    perguntas[2].alternativas[4] = "e) Busca: O(n log (n) ); Insercao: O(n);";

    perguntas[2].gabarito = 'd';

    perguntas[2].recompensa = 2;
    perguntas[2].punicao = 2;
}

void criarquarta2 (pergunta perguntas[6]) {

    perguntas[3].nivel = "Medio";

    perguntas[3].enunciado = "Dentre os algoritmos de ordenacao interna que operam por comparacao,\n"
    "o Merge Sort e o Insertion Sort possuem comportamentos distintos quanto ao uso de recursos.\n" 
    "Qual das alternativas descreve corretamente a relacao de tempo e espaco entre eles?\n";

    perguntas[3].alternativas[0] = "a) O Merge Sort eh mais rapido no pior caso, O(n log (n) ),mas exige mais espaco de memoria auxiliar, O(n),\n" 
    "enquanto o Insertion Sort eh mais lento no pior caso, O(n^2), mas consome espaco auxiliar constante, O(1).;";
    perguntas[3].alternativas[1] = "b) O Insertion Sort eh mais rapido no pior caso porque ordena os elementos \"in-place\" (no proprio vetor de entrada).;";
    perguntas[3].alternativas[2] = "c) Ambos possuem a mesma complexidade de tempo no pior caso, O(n log (n) ),\n"
    "diferindo apenas na complexidade de espaco.;";
    perguntas[3].alternativas[3] = "d) O Merge Sort utiliza menos memoria auxiliar do que o Insertion Sort porque divide o problema em partes menores.;";
    perguntas[3].alternativas[4] = "e) O Insertion Sort eh um algoritmo nao estavel, enquanto o Merge Sort eh necessariamente instavel e de tempo exponencial.;";

    perguntas[3].gabarito = 'a';

    perguntas[3].recompensa = 2;
    perguntas[3].punicao = 2;

}

void criarquinta2 (pergunta perguntas[6]) {

    perguntas[4].nivel = "Dificil";

    perguntas[4].enunciado = "Deseja-se remover um no intermediario P (que nao seja o primeiro nem o ultimo) de uma lista duplamente encadeada.\n" 
    "Assuma que voce ja possui o ponteiro direto apontando para o no P.\n" 
    "Quais atribuicoes de ponteiros sao estritamente necessarias e corretas para isolar P da lista sem perder a integridade da estrutura?";

    perguntas[4].alternativas[0] = "a) P->ant->prox = P->prox; e P->prox->ant = P->ant;";
    perguntas[4].alternativas[1] = "b) P->prox = P->ant; e P->ant = P->prox;";
    perguntas[4].alternativas[2] = "c) P->ant = NULL; e P->prox = NULL;";
    perguntas[4].alternativas[3] = "d) P->ant->ant = P->prox; e P->prox->prox = P->ant;";
    perguntas[4].alternativas[4] = "e) P = NULL; apenas, pois o coletor de lixo do C ajusta as referências automaticamente.";

    perguntas[4].gabarito = 'a';

    perguntas[4].recompensa = 3;
    perguntas[4].punicao = 3;

}

void criarsexta2 (pergunta perguntas[6]) {

    perguntas[5].nivel = "Dificil";

    perguntas[5].enunciado = "Sobre algoritmos de ordenacao interna e suas respectivas complexidades no pior caso, analise o comportamento do Quick Sort e do Merge Sort.\n" 
    "Qual alternativa expressa de maneira precisa as complexidades de tempo e espaco auxiliar desses algoritmos no pior caso?";

    perguntas[5].alternativas[0] = "a) Quick Sort possui tempo O(n log (n) ) e espaco O(1); Merge Sort possui tempo O(n^2) e espaco O(n).;";
    perguntas[5].alternativas[1] = "b) Quick Sort possui tempo O(n^2) e espaco auxiliar O(n) (devido a pilha de recursao);\n" 
    "Merge Sort possui tempo O(n log n) e espaco auxiliar O(n).;";
    perguntas[5].alternativas[2] = "c) Ambos possuem tempo O(n log (n) ) e espaco auxiliar O(1) no pior caso.;";
    perguntas[5].alternativas[3] = "d) Merge Sort possui tempo O(n log (n) ) e espaço auxiliar O(log (n) );\n" 
    "Quick Sort possui tempo O(n^2) e espaço auxiliar O(1);";
    perguntas[5].alternativas[4] = "e) Ambos possuem tempo de pior caso O(n^2) e espaco auxiliar quadratico O(n^2).;";

    perguntas[5].gabarito = 'b';

    perguntas[5].recompensa = 3;
    perguntas[5].punicao = 3;
}

void criartodas2 (pergunta p[6]) {

    criarprimeira2(p);
    criarsegunda2(p);
    criarterceira2(p);
    criarquarta2(p);
    criarquinta2(p);
    criarsexta2(p);

    for (int i = 0; i < 6; i ++) p[i].unidade = 2;
}

void encadear2 (tp_listad **caminho, pergunta perguntas2uni[]) {

    casa lista_caminho[10];

    especial sorte2uni;
    sorte2uni.caracteristica = "sorte";
    sorte2uni.deslocamento = 2;

    especial azar2uni;
    azar2uni.caracteristica = "azar";
    azar2uni.deslocamento = 2;

    lista_caminho[2].conteudo = "e";
    lista_caminho[2].e = sorte2uni;

    lista_caminho[4].conteudo = "e";
    lista_caminho[4].e = sorte2uni;

    lista_caminho[6].conteudo = "e";
    lista_caminho[6].e = azar2uni;

    lista_caminho[8].conteudo = "e";
    lista_caminho[8].e = azar2uni;

    int j = 0;
    for (int i = 0; i < 10; i ++) {

        if (lista_caminho[i].conteudo != "e") {
            
            lista_caminho[i].conteudo = "p"; 
            lista_caminho[i].p = perguntas2uni[j];
            j ++;

        } lista_caminho[i].numeracao = i + 1;

    }

    for (int i = 0; i < 10; i ++) insere_listad_no_fim (*caminho, lista_caminho[i]);

    tp_no *mov;
    mov = (*caminho)->ini;

    /*
    Pula-se as 11 primeiras casas, para não afetar
    as perguntas da primeira unidade.
    */
    for (int i = 0; i < 11; i++) mov = mov->prox;



}

#endif