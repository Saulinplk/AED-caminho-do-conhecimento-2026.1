#ifndef SM_CONTROL_H
#define SM_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "estrutura_pergunta.h"
#include "listad.h"
#include "jogador.h"
#include "pilha.h"

#define ANSI_RESET   "\x1b[0m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"
#define ANSI_BOLD    "\x1b[1m"

/*
Simplesmente embaralha as perguntas, em uma lista mesmo.
*/
void embaralhar(pergunta vetor[], int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        pergunta temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

/*
Empilha na ordem que tá na lista
*/
void reabastecer(tp_pilha *pilha, pergunta vetor_origem[]) {
    
    inicializa_pilha (pilha);
    
    /*
    Usa outro vetor, porque mesmo tentando passar por copia,
    o vetor tem um ponteiro de mesmo nome
    */
    pergunta outro[6];
    for(int i = 0; i < 6; i++) {
        outro[i] = vetor_origem[i];
    }
    
    /*
    Embaralha o outro sem ser o original
    */
    embaralhar(outro, 6);
    
    /*
    Empilha as perguntas na ordem nova sem mudar o vetor original,
    mas mudando o outro
    */
    for (int i = 0; i < 6; i++) {
        push(pilha, outro[i]);
    }
}

void obter (tp_pilha *pilha_da_unidade, pergunta vetor_da_unidade[], pergunta *pergunta_saida) {

    if (pilha_vazia(pilha_da_unidade)) {
        reabastecer (pilha_da_unidade, vetor_da_unidade);
    }
    
    /*
    Desempilhar após confirmar que a pilha não está vazia
    */
    pop(pilha_da_unidade, pergunta_saida);
}

void finalizar (tp_listad *caminho) {

    /*
    Assim como explicado na main, essa função apenas evita que o jogador
    acesse o inexistente caso o número tirado no dado seja maior que a diferença
    entre a casa final e a casa atual.
    */

    casa v1, v2, v3, v4, v5, v6;
    v1.conteudo = v2.conteudo = v3.conteudo = v4.conteudo = v5.conteudo = v6.conteudo =  "v";

    v1.numeracao = 31; v2.numeracao = 32; v3.numeracao = 33; v4.numeracao = 34; v5.numeracao = 35; v6.numeracao = 36;

    insere_listad_no_fim (caminho, v1);
    insere_listad_no_fim (caminho, v2);
    insere_listad_no_fim (caminho, v3);
    insere_listad_no_fim (caminho, v4);
    insere_listad_no_fim (caminho, v5);
    insere_listad_no_fim (caminho, v6);

}

/*
Essa função é para o desenvolvedor. Ela não é chamada ao jogar.
Pode-se usá-la pra ver detalhadamente se cada casa do caminho
é uma pergunta ou um especial, sem percorrer cada uma delas como jogador.
*/
void ver (tp_listad *caminho) {

    tp_no *mov;
    mov = caminho->ini;

    for (int i = 0; i < 16; i ++) {

        printf("| %s | -> ", mov->info.conteudo);

        mov = mov->prox;

    } printf("| NULL |\n");

    for (int i = 0; i < 16; i ++) {

        if (i < 10) printf("  %d      ", i);
        else printf("  %d     ", i);
    }

}

/*
Caso a casa seja uma pergunta, essa função é aplicada a ela.
Basicamente ela printa o enunciado, mostra as alternativas
e recompensa ou pune o jogador dependendo da resposta dele.
*/
void perguntar (
    jogador *j, 
    pergunta perguntas1uni[], pergunta perguntas2uni[], pergunta perguntas3uni[],
    tp_pilha *pilha1, tp_pilha *pilha2, tp_pilha *pilha3
) {
    pergunta essa_pergunta;
    int unidade_atual = j->mov->info.p.unidade; // Para não misturar as pilhas,
    // pois as perguntas de cada unidade são independente das de outra unidade

    
    if (unidade_atual == 1) obter (pilha1, perguntas1uni, &essa_pergunta);
    
    else if (unidade_atual == 2) obter (pilha2, perguntas2uni, &essa_pergunta);
    
    else if (unidade_atual == 3) obter (pilha3, perguntas3uni, &essa_pergunta);
    
    else return; // Caso caia em uma caia vazia ou especial, sem unidade definida
    

    printf (ANSI_CYAN ">>> PERGUNTA DE NIVEL [%s] (Unidade %d - Casa %d) <<<\n" ANSI_RESET, 
            essa_pergunta.nivel, unidade_atual, j->mov->info.numeracao);
    printf ("---------------------------------------------------------------\n");
    printf ("%s\n", essa_pergunta.enunciado);
    printf ("---------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) printf("  %s\n", essa_pergunta.alternativas[i]);
    
    printf ("---------------------------------------------------------------\n");

    char resposta;
    printf ("Qual eh a resposta? "); 
    scanf (" %c", &resposta);

    /*
    Caso ele acerte:
    */
    if (tolower (resposta) == essa_pergunta.gabarito) { 
        j->pontos += 10; // Aumenta os pontos do jogador
        j->quantas_acertou++;

        /*
        O laço abaixo salva a pergunta na lista de perguntas que o jogador acertou.
        Isso é um campo dentro da struct jogador.
        */

        for (int i = 0; i < 6; i++) {
            if (strcmp (j->acertou[i].enunciado, "w") == 0) {
                j->acertou[i] = essa_pergunta; 
                break; 
                
            }
        }

        /*
        Você pode estar se perguntando qual é o sentido desse "w".
        Eu precisava garantir que a primeira pergunta acertada não fosse
        substituída pela segunda, e assim por diante, então criei esse critério de
        "se o enunciado é w, o espaço da lista tá vazio e pode receber uma pergunta".

        Mas porquê w? Inicialmente, eu comparava as strings diretamente, com ==.
        Eu sabia que isso só comparava o primeiro caractere de cada uma. Eu escolhi
        "w" porque nenhum enunciado começa com a letra w.
        Posteriormente, lendo arquivos de Saulo, eu descobri a função strcmp, mais adequada
        para a comparação de strings. Simplesmente substituí o == por strcmp ( == 0),
        mantendo o "w".
        */

        printf(ANSI_GREEN "\n[ACERTOU!] Voce avancou %d casas no tabuleiro.\n" ANSI_RESET, essa_pergunta.recompensa);
        for (int i = 0; i < essa_pergunta.recompensa; i++) (*j).mov = (*j).mov->prox;
        /*
        Esse laço apenas dá uma vantagem ao jogador, movendo ele para frente antes mesmo
        de ele jogar o dado.
        */
    }

    else { // Analogamente, quando o jogador erra, ele é punido.
        j->pontos -= 10; 
        j->quantas_errou++;

        
        for (int i = 0; i < 6; i++) {
            if (strcmp(j->errou[i].enunciado, "w") == 0) {
                j->errou[i] = essa_pergunta; 
                break;
            }
        }

        printf(ANSI_RED "\n[ERROU!] Voce voltou %d casas no tabuleiro.\n" ANSI_RESET, essa_pergunta.punicao);
        for (int i = 0; i < essa_pergunta.punicao; i++) (*j).mov = (*j).mov->ant;
    }

    /*
    Essa função está dentro do bloco de if else.
    Ou seja, ela sempre acontece, independetemente se o jogador acerta ou erra.
    Ela mostra a casa que o jogador acabou por cair, seja depois de avançar ou de voltar.
    */
    printf("(Agora %s esta na casa %d)\n\n", j->nome, j->mov->info.numeracao);
}

/*
A função aplicar aplica a sorte ou o azar da casa especial.
Ela está para a casa especial assim como a função perguntar
está para a casa de pergunta.
*/

void aplicar (especial e, jogador *j) {

    if (strcmp (e.caracteristica, "sorte") == 0) { //Sorte significa avançar no tabuleiro
        for (int i = 0; i < e.deslocamento; i++) (*j).mov = (*j).mov->prox;
        
        printf(ANSI_GREEN "[SORTE!] %s, voce avancou %d casas no tabuleiro!\n" ANSI_RESET, j->nome, e.deslocamento);
    } 

    else { // Qualquer outra coisa (na prática, azar) significa voltar no tabuleiro
        for (int i = 0; i < e.deslocamento; i++) (*j).mov = (*j).mov->ant;

        printf(ANSI_YELLOW "[AZAR!] Que pena %s, voce voltou %d casas no tabuleiro.\n" ANSI_RESET, j->nome, e.deslocamento);
    }

    /*
    O jogador também sofre deslocamento caso caia em uma casa especial.
    */
    printf("(Agora %s esta na casa %d)\n\n", j->nome, j->mov->info.numeracao);
}

/*
A função operar decide se ela vai tratar a casa como uma
pergunta ou como um especial.
*/

void operar (jogador *j, casa c, 
             pergunta p1[], pergunta p2[], pergunta p3[], 
             tp_pilha *pilha1, tp_pilha *pilha2, tp_pilha *pilha3) 
{
    
    if (strcmp(c.conteudo, "p") == 0)  perguntar (j, p1, p2, p3, pilha1, pilha2, pilha3);
    // As casas com conteúdo "p" são perguntas.
    

    if (strcmp(c.conteudo, "e") == 0) aplicar (c.e, j);
    // As casas com conteúdo "e" são especiais.
    
}

/*
O nó estatística é uma estrutura auxiliar para guardar quantas vezes
cada jogador caiu em cada casa em uma árvore binária.
*/

no_estatistica* registrar_visita (no_estatistica *raiz, int casa_atual /* Isso é a numeração DA CASA */) {


    /*
    Caso seja a primeira vez que o jogador caiu nessa casa:
    */
    if (raiz == NULL) {

        no_estatistica *novo = (no_estatistica*) malloc (sizeof (no_estatistica));

        novo->numero_casa = casa_atual;
        novo->vezes_que_caiu = 1; // (É a primeira vez)

        novo->esq = NULL;
        novo->dir = NULL;
        // Como esse nó é novo, ele não tem filho.

        return novo;
    }

    // Caso o jogador já tenha caído nessa casa
    if (casa_atual == raiz->numero_casa) raiz->vezes_que_caiu ++;
    
    /*
    Se a numeração da casa atual for menor que a da raíz, ela vai pra esquerda.
    */
    else if (casa_atual < raiz->numero_casa) raiz->esq = registrar_visita (raiz->esq, casa_atual);
    // Atualiza-se a raíz
    
    /*
    Se a numeração da casa for maior OU igual que a da raíz, ela vai pra direita.
    */
    else {

        raiz->dir = registrar_visita (raiz->dir, casa_atual); // Atualiza-se a raíz
    }

    return raiz;
}

/*
Imprimir quantas vezes cada jogador caiu em cada casa
*/
void exibir (no_estatistica *raiz, char *nome_jogador) { 

    if (raiz != NULL) { // Garante que a função volte

        /*
        Imprime primeiro os mais à esquerda,
        */
        exibir (raiz->esq, nome_jogador); 
        
        printf ("  -> %s caiu na casa %-2d: %d vez(es)\n", nome_jogador, raiz->numero_casa, raiz->vezes_que_caiu);
        
        /*
        e depois os mais à direita
        */
        exibir (raiz->dir, nome_jogador);

        /*
        OBS:
        A preferência é dada para os nós à esquerda (contanto que não sejam nulos),
        e a ordem é crescente justamente da esquerda pra direita.
        
        Portanto, como o exibir do raiz->esq acontece antes do 
        raiz->dir, esse é o percurso em ordem.
        */
    }
}

void imprime_arvore (tp_arvore arvore, char *nome_jogador) {

    printf("\n===================================\n");
    printf("  ESTATISTICAS DE CASAS: %s\n", nome_jogador); 
    /*
    Isso vai ser alternado pra cada jogador pela função revezar
    */
    printf("===================================\n");

    exibir (arvore.raiz, nome_jogador); 
    
    printf("===================================\n");
}

void jogar (jogador *j, tp_listad *caminho, 
            pergunta p1[], pergunta p2[], pergunta p3[], 
            tp_pilha *pilha1, tp_pilha *pilha2, tp_pilha *pilha3) 
{
    if (strcmp (j->mov->info.conteudo, "v") == 0) return;
    /*
    Se for detectado que é uma casa vazia, ou seja de segurança,
    o código já para, pra evitar dele tentar tratar essa casa
    como uma casa operável (pergunta ou especial), o que não é o caso.
    */
    
    system("cls"); // Para evitar que as jogadas anteriores continuem poluindo a tela

    printf (ANSI_BLUE "===============================================================\n" ANSI_RESET);
    printf (ANSI_BOLD "  VEZ DE: %-15s " ANSI_RESET ANSI_BLUE "| PONTOS: %-4d | ACERTOS: %d | ERROS: %d\n", 
            j->nome, j->pontos, j->quantas_acertou, j->quantas_errou);
    printf (ANSI_BLUE "===============================================================\n\n" ANSI_RESET);

    if (strcmp (j->mov->info.conteudo, "c") == 0) printf("[!] %s acabou de comecar na casa 0\n", j->nome);
    
    /*
    A função jogar apenas se preocupa com o fato de a casa ser
    OPERÁVEL ou não. Como ela vai ser operada
    (pergunta ou especial), a própria função operar
    já cuida disso.
    */
    operar (j, j->mov->info, p1, p2, p3, pilha1, pilha2, pilha3);

    printf ("Pressione qualquer letra para jogar o dado (Nao vale Enter): "); 
    char esperar; scanf (" %c", &esperar);
    /*
    O getchar tava dando problema.

    Por isso obriguei o usuário a atribuir um valor a uma variável.
    Não para usá-la, mas para ele ter a impressão de que ele fez 
    alguma coisa para jogar o dado.
    */

    int avanco = (rand () % 6) + 1; // Essa linha realmente joga o dado.
    
    // Avança o jogador conforme o número em que o dado caiu
    for (int i = 0; i < avanco; i++) j->mov = j->mov->prox; 
    
    // Como o jogador acabou de cair em uma casa nova, essa visita deve ser registrada.
    j->estatisticas.raiz = registrar_visita (j->estatisticas.raiz, j->mov->info.numeracao);

    printf ("O dado caiu em %d ", avanco);
    printf ("(Agora %s esta na casa %d)\n", j->nome, j->mov->info.numeracao);

    if (strcmp (j->mov->info.conteudo, "v") == 0) {
        printf ("\nParabens! %s chegou ao final do tabuleiro.\n", j->nome);
        return;
    }

    /*
    Você pode estar se perguntando porque essa comparação foi feita duas vezes.

    Se o conteúdo da casa era vazio ("v") ANTES da casa atual ser operada,
    então o jogador JÁ ESTAVA na casa vazia. 

    A função revezar vai chamar o jogador denovo, e não faz sentido
    ficar parabenizando ele repetidamente. Faz-se isso apenas uma vez.

    Por outro lado, se após a operação da casa, o conteúdo for "v",
    é porque o jogador acabou de cair nessa casa devido à operação.
    Aí sim, ele é parabenizado.
    */
}

void salvar (jogador jogadores[], int quantidade) {

    FILE *arquivo = fopen ("ranking.txt", "w"); // Cria o arquivo pra guardar no disco

    fprintf (arquivo, "%d\n", quantidade);

    for (int i = 0; i < quantidade; i++) {

        int pontuacao = jogadores[i].pontos;

        pontuacao *= (jogadores[i]).quantas_acertou;
        pontuacao += (jogadores[i]).mov->info.numeracao;
        /*
        Basicamente, quanto mais perguntas o jogador acerta, maior
        é a pontuação dele.

        Esse info.numeração é um critério de desempate.

        Imagine que dois jogadores acertaram e erraram a mesma quantidade de questões.

        Nesse caso, a sorte decidirá quem fica com mais pontos.
        Isso significa que quem tiver mais sorte no dado, vai cair em uma casa mais distante,
        que tem uma numeração maior, obtendo, portanto, uma pontuação maior.
        */

        // Pra cada jogador, salva-se a pontuação correspondente ao nome dele no arquivo.
        fprintf(arquivo, "%s %d\n", jogadores[i].nome, pontuacao);
        
    }

    fclose (arquivo); 
}

/*
Essa struct não afeta diretamente a jogabilidade.
Por isso, ela está no final.

Ela é mais pra uma análise pós-jogo, mostrando um rank.
*/

typedef struct {

    char nome[99];

    int pontuacao;

    /*
    Simplesmente observa-se com quantos pontos cada jogador ficou.
    */

} dados_ranking;

void mostrar_rank () {

    FILE *arquivo = fopen("ranking.txt", "r");

    int qtd;

    fscanf (arquivo, "%d", &qtd);
    /*
    Utiliza-se o arquivo ranking.txt para ler a pontuação referente
    a cada jogador.
    */
    dados_ranking lista[qtd];

    /*
    Vale lembrar que atualmente, o C já permite
    o uso de variáveis como tamanho de vetor.
    */


    for (int i = 0; i < qtd; i++) fscanf(arquivo, "%s %d", lista[i].nome, &lista[i].pontuacao);
    /*
    qtd é a quantidade de jogadores. Mostra-se a pontuação
    para cada jogador.
    */
    
    fclose(arquivo); 

    /*
    Usa-se o simples Bubble Sort para ordenar os jogadores no rank
    porque o número de jogadores é MUITO baixo (no máximo 4).

    Utilizar um Heap Sort, por exemplo, seria muito exagero,
    e até pior para o desempenho, visto que regiria todo
    um processo de conversão para a estrutura Heap. 
    */

    for (int i = 0; i < qtd - 1; i++) {

        for (int j = 0; j < qtd - i - 1; j++) {

            if (lista[j].pontuacao < lista[j+1].pontuacao) { 

                dados_ranking temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    } 
    
    printf("\n\nRANK\n\n");

    for (int i = 0; i < qtd; i++) printf("%do Lugar: %s - Pontuacao: %d\n", i + 1, lista[i].nome, lista[i].pontuacao);
    
}

void revezar (jogador jogadores[], int quantidade, tp_listad *caminho,
              pergunta p1[], pergunta p2[], pergunta p3[], 
              tp_pilha *pilha1, tp_pilha *pilha2, tp_pilha *pilha3) 
{
   /*
   Esse laço remove o lixo presente nas variáveis
   de campo dos jogadores. É como se fosse uma função
   "inicializa_jogadores."
   */
    for (int i = 0; i < quantidade; i++) {
        jogadores[i].pontos = 0;
        jogadores[i].estatisticas.raiz = NULL; 
        jogadores[i].quantas_acertou = 0;
        jogadores[i].quantas_errou = 0;
    }
    
    /*
    Aqui, define-se o conceito da "pergunta inexistente".
    Basicamente, isso garante que na lista de perguntas acertadas ou erradas,
    aquele espaço está livre para receber um novo enunciado.

    Isso evita que, caso o jogador acerte várias perguntas, apenas a última
    seja exposta.
    */

    pergunta nenhuma; 
    nenhuma.enunciado = "w";

    /*
    Isso prepara a lista de acertadas e erradas para ser
    utilizada. Sem o "w" da "pergunta nenhuma" como conteúdo,
    cada espaço da lista não poderia receber um enunciado.
    */

    for (int i = 0; i < quantidade; i++) {

        for (int j = 0; j < 6; j++) jogadores[i].acertou[j] = nenhuma;
        for (int j = 0; j < 6; j++) jogadores[i].errou[j] = nenhuma;
    }

    int i = 0;
    while (1) { 
        int stop = 0;

        /*
        Seria injusto deixar um jogador ficar com vantagem
        só porque ele foi o primeiro a jogar o dado e respondeu
        as perguntas cronologicamente antes dos outros jogadores.  

        Por isso, a verificação de se a casa é vazia (tem "v" como conteúdo)
        só ocorre ao final do ciclo (quando o resto da divisão inteira de i 
        volta a ser múltiplo da quantidade de jogadores.)
        */
        if (i % quantidade == 0) 
            for (int k = 0; k < quantidade; k++) 
                if (strcmp (jogadores[k].mov->info.conteudo, "v") == 0) stop = 1;
            
        if (stop) break;
        /*
        Eu uso esse stop pra quebrar o while porque quando eu usava o break
        direto, quem parava era o for, porque é o loop mais interno.
        */

        /*
        Para cada vez que se reveza o resto da divisão de i pela
        quantidade de jogadores, permite-se que o jogador cujo índice 
        na lista é o resto da divisão, finalmente jogue.
        */

        jogar(&jogadores[i % quantidade], caminho, p1, p2, p3, pilha1, pilha2, pilha3); 
        i++;
    }

    /*
    Após a confirmação de que algum jogador chegou no fim 
    (casa com conteúdo "v") após o fechamento do ciclo de 
    vezes dos jogadores, o while é encerrado, ou seja, 
    fim de jogo.
    */
    printf("\nFim de jogo\n");

    /*
    Observe:
    Dois jogadores podem chegar ao fim em momentos cronologicamente
    diferentes simplesmente porque um é o jogador 1 e o outro é
    o jogador 4, mas tendo jogado o dado a mesma quantidade de vezes.

    Se isso acontecer, AMBOS serão considerados vencedores.
    Nesse caso, o jogador com maior pontuação não será necessariamente
    O que jogou o dado primeiro, mas sim o que acertou mais questões
    ou o que chegou mais perto do limite do tabuleiro (nas casas de segurança).
    */

    for (int k = 0; k < quantidade; k++) 
        if (strcmp(jogadores[k].mov->info.conteudo, "v") == 0) printf("\n%s eh vencedor\n", jogadores[k].nome);

    /*
    Mostra o rank dos jogadores.
    */

    for (int k = 0; k < quantidade; k++)
        imprime_arvore (jogadores[k].estatisticas, jogadores[k].nome); 
    
    /*
    Cria-se o arquivo para guardar o rank em disco
    */
    salvar (jogadores, quantidade);
    mostrar_rank();
    
    /*
    Mostra-se quais casas cada jogador acertou.
    */
    for (int k = 0; k < quantidade; k++) {

        printf ("\nPerguntas que %s acertou:\n", jogadores[k].nome);
        // Roda apenas a quantidade real de acertos do jogador
        for (int j = 0; j < jogadores[k].quantas_acertou; j++) {
            printf(" - %s\n", jogadores[k].acertou[j].enunciado);
        }
        if (jogadores[k].quantas_acertou == 0) printf(" - Nenhuma pergunta.\n");
    }

    /*
    Mostra-se quais casas cada jogador errou.
    */
    for (int k = 0; k < quantidade; k++) {
        printf("\nPerguntas que %s errou:\n", jogadores[k].nome);
        // Roda apenas a quantidade real de erros do jogador
        for (int j = 0; j < jogadores[k].quantas_errou; j++) {
            printf(" - %s\n", jogadores[k].errou[j].enunciado);
        }
        if (jogadores[k].quantas_errou == 0) printf(" - Nenhuma pergunta.\n");
    }

    /*
    Guarda em disco as perguntas que cada jogador acertou e errou.
    Para isso, analogamente, repete-se o trecho de código acima,
    mas com fprints ao invés de prints e passando o arquivo 
    respondidas.txt como mais um argumento.
    */

    FILE *arquivo = fopen ("respondidas.txt", "w");

    for (int k = 0; k < quantidade; k++) {

        fprintf(arquivo, "\nPerguntas que %s acertou:\n", jogadores[k].nome);

        for (int j = 0; j < jogadores[k].quantas_acertou; j++) 
            fprintf(arquivo, " - %s\n", jogadores[k].acertou[j].enunciado);
        
        if (jogadores[k].quantas_acertou == 0) fprintf(arquivo, "Nenhuma.\n");
    }

    for (int k = 0; k < quantidade; k++) {

        fprintf(arquivo, "\nPerguntas que %s errou:\n", jogadores[k].nome);

        for (int j = 0; j < jogadores[k].quantas_errou; j++) 
            fprintf(arquivo, " - %s\n", jogadores[k].errou[j].enunciado);
        
        if (jogadores[k].quantas_errou == 0) fprintf(arquivo, "Nenhuma\n");
    }

    fclose(arquivo);
}


#endif