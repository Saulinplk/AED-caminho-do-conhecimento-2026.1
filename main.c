#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "estrutura_pergunta.h"
#include "listad.h"
#include "jogador.h"
#include "pilha.h"

#include "sm_unidade1.h"
#include "sm_unidade2.h"
#include "sm_unidade3.h"

#include "sm_control.h"

int main () { srand (time (NULL));

    /* Extrair as perguntas */

    pergunta perguntas1uni[6]; criartodas1 (perguntas1uni);
    pergunta perguntas2uni[6]; criartodas2 (perguntas2uni);
    pergunta perguntas3uni[6]; criartodas3 (perguntas3uni);

    /* Preencher as casas no caminho */

    tp_listad *caminho;
    caminho = inicializa_listad ();

    encadear1 (&caminho, perguntas1uni);
    encadear2 (&caminho, perguntas2uni);
    encadear3 (&caminho, perguntas3uni);


    tp_pilha pilha_perguntas1uni; inicializa_pilha (&pilha_perguntas1uni);
    tp_pilha pilha_perguntas2uni; inicializa_pilha (&pilha_perguntas2uni);
    tp_pilha pilha_perguntas3uni; inicializa_pilha (&pilha_perguntas3uni);

    finalizar (caminho); // Isso apenas adiciona as 6 casas de segurança no final.

    tp_no *mov;
    mov = caminho->ini;

    int numero = 0;

    while (mov != NULL) {

        mov->info.numeracao = numero; 
        mov = mov->prox; numero ++;
    }
/*
    mov = caminho->ini;

    
    // Essa função não é necessária para o funcionamento do código, 
    // mas é ótima para testar bugs. Ela permite "ver" se o caminho
    // tá na ordem certinha.
    

    while (mov != NULL) {

        printf("%d\n", mov->info.numeracao); mov = mov->prox;

    }
    return 0;
*/
    int quantidade; // 2 a 4 jogadores
    while (1) {

        printf("\nQuantos jogadores? (Minimo 2, maximo 4) ");
        scanf("%d", &quantidade);

        if ((quantidade >= 2) && (quantidade <= 4)) break;

        printf("\nErro: a quantidade de jogadores deve ser no minimo 2 e no maximo 4.\n");

    }

    /*
    Uma lista pra ficar revezando os jogadores através do índice
    */

    jogador jogadores[quantidade];

    for (int i = 0; i < quantidade; i ++) {

        jogadores[i].mov = caminho->ini;

        printf("\nQual o nome do jogador %d? ", i + 1); 
        scanf ("%s", jogadores[i].nome);

        //printf("\nEntao o jogador %d eh %s", i + 1, jogadores[i].nome);
        /*
        Esse printf é opcional.
        Ele serve pra ver se o programa realmente conseguiu ler os nomes dos jogadores.
        */

    }

    /*
    A função revezar é a que permite o usuário interagir com o jogo. Ela reveza a vez dos jogadores,
    e permite a interação entre eles e o caminho, com as perguntas e os especiais.
    */

    revezar (
        jogadores, quantidade, caminho, 
        perguntas1uni, perguntas2uni, perguntas3uni, 
        &pilha_perguntas1uni, &pilha_perguntas2uni, &pilha_perguntas3uni
    );

    return 0;
}