#ifndef LISTAD_H
#define LISTAD_H

#include <stdio.h>
#include <stdlib.h>

#include "casa.h"

typedef /*int*/ casa tp_item /* Lembrete: a casa pode ser pergunta ou especial. O resto aqui é tudo igual */; 

//dados estruturado que representa o descritor
typedef struct tp_no_aux {   
  struct tp_no_aux *ant;  
  tp_item info;  
  struct tp_no_aux *prox;   
} tp_no; 

//dado estruturado que representa a lista
typedef struct {   
  tp_no *ini;   
  tp_no *fim;   
//  int tamanho;   
} tp_listad;

//aloca-se memória para o descritor (explicado no ínicio deste arquivo) e faz o seus ponteiros apontarem para o Nulo
tp_listad *inicializa_listad(){
   tp_listad *lista=(tp_listad*) malloc(sizeof(tp_listad));   
   lista->ini = NULL;
   lista->fim = NULL;   
 // lista->tamanho = 0;   
   return lista;
}  


int listad_vazia(tp_listad *lista) {
	if ( (lista->ini == NULL) ) 
		return 1;
	return 0;	
}

//Aloca um nó da lista
tp_no *aloca() {
	tp_no* pt;
	pt=(tp_no*) malloc(sizeof(tp_no));
	return pt;
}

//insere um novo nó na lista 
int insere_listad_no_fim (tp_listad *lista, tp_item e){   
  tp_no *novo;   
  novo=aloca();
  if (!novo) return 0;
  novo->info = e;  
  novo->prox = NULL; 
  if ( listad_vazia(lista) ){ //Se for o primeiro elemento da lista
     novo->ant = NULL; 
     lista->ini = lista->fim = novo;
     }  
  else {   
     novo->ant = lista->fim; 
     lista->fim->prox = novo;
     lista->fim = novo;
     }  
  //lista->tamanho++; 

  return 1;   
}        

//imprime os conteúdos da lista (de frente para trás ou de trás pra frente)                
void imprime_listad(tp_listad *lista, int ordem) {
	if (lista==NULL)
		printf("Lista não inicializada");
	else {
     tp_no *atu;     
     switch (ordem) {
        case 1: atu = lista->ini;
                while (atu != NULL) {
                   printf(/*"%d "*/"%s ", atu->info.p.enunciado);
                   atu=atu->prox;           
                   }
                break;   
        case 2: atu = lista->fim;
                while (atu != NULL) {
                   printf(/*"%d "*/"%s ", atu->info.p.enunciado);
                   atu=atu->ant;           
                   }
                
    default: printf("codigo invalido");        
     }
	}
     printf("\n");
}


        

//Com base em um conteúdo, retorna-se o endereço do nó que contém o conteúdo

/*
tp_no * busca_listade (tp_listad *lista, tp_item e){   
  tp_no *atu;
  atu = lista->ini;
  while ( (atu != NULL) && (atu->info != e) ) { 
        atu=atu->prox;}
  return atu;
}        
*/

//Retira da memória todos os nós da lista e também o descritor
tp_listad * Destroi_listad (tp_listad *lista){   
  tp_no *atu;
  atu = lista->ini;
  while (atu != NULL)  { 
        lista->ini = atu->prox;
        free(atu);
        atu=lista->ini;
		}
  free(lista);
  return NULL;
}  

#endif