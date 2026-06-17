#ifndef SM_UNIDADE3_H
#define SM_UNIDADE3_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "estrutura_pergunta.h"
#include "listad.h"
#include "jogador.h"
#include "pilha.h"

/*
Análogo ao arquivo da segunda unidade.
Mas pula 21 casas ao invés de 11.
*/

void criarprimeira3(pergunta p[6]) {

    p[0].nivel = "Facil";

    p[0].enunciado = "As arvores binarias de busca classicas podem ficar desbalanceadas\n" 
    "se os elementos forem inseridos em uma ordem específica (como uma sequência ja ordenada),\n" 
    "fazendo com que o tempo de busca piore.\n" 
    "Qual é o pior caso de tempo de busca em uma arvore binaria completamente desbalanceada\n" 
    "(que se comporta como uma lista encadeada)?";

    p[0].alternativas[0] = "a) O(1)";
    p[0].alternativas[1] = "b) O(log n)";
    p[0].alternativas[2] = "c) O(n)";
    p[0].alternativas[3] = "d) O(nlog n)";
    p[0].alternativas[4] = "e) O(n^2)";

    p[0].gabarito = 'c';

    p[0].recompensa = 1;
    p[0].punicao = 1;
}

void criarsegunda3 (pergunta p[6]) {

    p[1].nivel = "Facil";

    p[1].enunciado = "As arvores digitais (também conhecidas como Tries)\n" 
    "sao estruturas de dados muito eficientes para armazenar e buscar um tipo específico de informacao.\n" 
    "Qual eh a principal aplicacao das arvores digitais no desenvolvimento de software?";

    p[1].alternativas[0] = "a) Armazenar numeros reais e gerenciar memoria RAM de forma sequencial.";
    p[1].alternativas[1] = "b) Armazenar strings (palavras/chaves) para busca de prefixos e corretores ortograficos.";
    p[1].alternativas[2] = "c) Balanceamento automatico de chaves criptograficas de tamanho fixo.";
    p[1].alternativas[3] = "d) Ordenacao rapida de vetores de structs de jogadores.";
    p[1].alternativas[4] = "e) Compactacao de arquivos binarios pesados e imagens.";

    p[1].gabarito = 'b';

    p[1].recompensa = 1;
    p[1].punicao = 1;
}

void criarterceria3 (pergunta p[6]) {

    p[2].nivel = "Medio";

    p[2].enunciado = "O balanceamento de uma Arvore AVL é controlado estritamente pelo fator de balanceamento (FB) de cada no,\n" 
    "que calcula a diferença entre as alturas das suas subarvores.\n" 
    "Um no é considerado desbalanceado, exigindo uma rotacao,\n" 
    "quando seu fator de balanceamento atinge no minimo (em modulo) quais valores?";

    p[2].alternativas[0] = "a) FB = 0 ou FB = 1";
    p[2].alternativas[1] = "b) FB = 2 ou FB = -2";
    p[2].alternativas[2] = "c) FB = 3 ou FB = -3";
    p[2].alternativas[3] = "d) Qualquer valor maior que 1, ignorando valores negativos.";
    p[2].alternativas[4] = "e) Apenas quando FB = -1.";

    p[2].gabarito = 'b';

    p[2].recompensa = 2;
    p[2].punicao = 2;
}

void criarquarta3 (pergunta p[6]) {

    p[3].nivel = "Medio";

    p[3].enunciado = "As Arvores B e B+ sao estruturas de dados balanceadas projetadas especificamente\n" 
    "para funcionar de forma eficiente em sistemas de armazenamento em disco (como HDs e SSDs).\n" 
    "Qual é a principal característica arquitetural de uma Arvore B que a diferencia de uma arvore binaria tradicional?";
    
    p[3].alternativas[0] = "a) Ela possui apenas uma subarvore esquerda e nenhuma direita.";
    p[3].alternativas[1] = "b) Cada no pode conter múltiplas chaves e múltiplos ponteiros para filhos.";
    p[3].alternativas[2] = "c) Ela armazena chaves apenas em suas folhas, deixando a raiz vazia.";
    p[3].alternativas[3] = "d) Ela é uma árvore estritamente digital que armazena apenas caracteres individuais.";
    p[3].alternativas[4] = "e) Seus nos mudam de cor entre preto e vermelho a cada insercao.";

    p[3].gabarito = 'b';

    p[3].recompensa = 2;
    p[3].punicao = 2;
}

void criarquinta3 (pergunta p[6]) {

    p[4].nivel = "Dificil";

    p[4].enunciado = "As Arvores Rubro-Negras garantem o balanceamento através de um conjunto estrito de propriedades\n" 
    "relacionadas as cores de seus nos (vermelho ou preto).\n" 
    "Qual das alternativas abaixo apresenta uma propriedade obrigatoria e verdadeira de uma Arvore Rubro-Negra?";

    p[4].alternativas[0] = "a) Todo no folha (NIL) deve ser obrigatoriamente vermelho.";
    p[4].alternativas[1] = "b) Se um no é vermelho, ambos os seus filhos devem ser obrigatoriamente vermelhos também.";
    p[4].alternativas[2] = "c) A raiz da arvore pode ser vermelha ou preta, dependendo da quantidade de rotacoes.";
    p[4].alternativas[3] = "d) Para cada no, todos os caminhos simples dele até suas folhas descendentes contêm o mesmo número de nos pretos.";
    p[4].alternativas[4] = "e) Uma arvore rubro-negra nunca pode ter dois nos pretos seguidos no mesmo caminho.";

    p[4].gabarito = 'd';

    p[4].recompensa = 3;
    p[4].punicao = 3;
    
}

void criarsexta3 (pergunta p[6]) {

    p[5].nivel = "Dificil";

    p[5].enunciado = "Ao realizar uma insercao em uma Arvore AVL, o balanceamento pode ser quebrado, exigindo rotacoes.\n" 
    "Suponha que você inseriu um elemento que causou um desbalanceamento para a esquerda na subarvore direita de um no\n" 
    "(caso Direita-Esquerda, ou RL). Quais rotacoes devem ser feitas, respectivamente, para corrigir a arvore?";

    p[5].alternativas[0] = "a) Uma rotacao simples para a esquerda na raiz desbalanceada.";
    p[5].alternativas[1] = "b) Uma rotacao simples para a direita no filho e depois uma para a esquerda no neto.";
    p[5].alternativas[2] = "c) Uma rotacao simples para a direita no filho direito e depois uma rotacao simples para a esquerda no no desbalanceado.";
    p[5].alternativas[3] = "d) Duas rotacoes seguidas para a direita no no desbalanceado.";
    p[5].alternativas[4] = "e) Nenhuma rotacao, pois o caso Direita-Esquerda se resolve apenas alterando os fatores de balanceamento.";

    p[5].gabarito = 'c';

    p[5].recompensa = 3;
    p[5].punicao = 3;

}

void criartodas3 (pergunta p[6]) {

    criarprimeira3(p);
    criarsegunda3(p);
    criarterceria3(p);
    criarquarta3(p);
    criarquinta3(p);
    criarsexta3(p);

    for (int i = 0; i < 6; i ++) p[i].unidade = 3;

}

void encadear3 (tp_listad **caminho, pergunta perguntas3uni[]) {

    casa lista_caminho[10];

    especial sorte3uni;
    sorte3uni.caracteristica = "sorte";
    sorte3uni.deslocamento = 3;

    especial azar3uni;
    azar3uni.caracteristica = "azar";
    azar3uni.deslocamento = 2;

    lista_caminho[3].conteudo = "e";
    lista_caminho[3].e = sorte3uni;

    lista_caminho[5].conteudo = "e";
    lista_caminho[5].e = sorte3uni;

    lista_caminho[7].conteudo = "e";
    lista_caminho[7].e = azar3uni;

    lista_caminho[9].conteudo = "e";
    lista_caminho[9].e = azar3uni;



    int j = 0;
    for (int i = 0; i < 10; i ++) {

        if (lista_caminho[i].conteudo != "e") {
            
            lista_caminho[i].conteudo = "p"; 
            lista_caminho[i].p = perguntas3uni[j];
            j ++;

        } lista_caminho[i].numeracao = i + 1;

    }

    for (int i = 0; i < 10; i ++) insere_listad_no_fim (*caminho, lista_caminho[i]);

    tp_no *mov;
    mov = (*caminho)->ini;

    /*
    Pula-se as 21 primeiras casas pra não afetar
    as perguntas da primeira e da segunda unidade.
    */
    for (int i = 0; i < 21 ; i++) mov = mov->prox;



}

#endif