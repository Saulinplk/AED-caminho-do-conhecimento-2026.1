#ifndef CASA_H
#define CASA_H

#include <stdio.h>
#include <string.h>

#include "estrutura_pergunta.h"

typedef struct casa {

    /*
    Cada casa ou é pergunta ou é especial. Se ela é um campo, o outro é vazio.

    O conteúdo (geralmente p ou e, salvo exceções*) serve pras funções saberem qual campo
    é operável e qual campo é o vazio.

    * Não vem ao caso agora, mas só pra não deixar a curiosidade voando, as exceções são "v", de vazio,
    e "c", de começo.
    O caminho tem 37 casas:
    1 inicial de segurança "c" (pra evitar bugs caso o jogador erre a primeira pergunta e não tenha pra onde voltar);
    30 casas operáveis (10 pra cada unidade);
    6 casas de segurança no final (Pra se o jogador estiver na última casa e tirar 6 no dado, ele não acessar o inexistente);
    Essas casas de segurança são inoperáveis e as do final têm conteúdo "v".

    */


    const char *conteudo; 

    pergunta p;
    
    especial e;

    int numeracao;

} casa;

#endif